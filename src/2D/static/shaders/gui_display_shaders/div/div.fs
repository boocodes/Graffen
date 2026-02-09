#version 330 core
out vec4 FragColor;

uniform vec4 color;            
uniform vec4 border_color;     
uniform vec4 border_width;
uniform vec2 size;
uniform vec4 border_radius;
uniform vec2 position;
uniform float smoothing;

in vec2 fragPos;

float roundedRectSDF(vec2 p, vec2 b, vec4 r) {
    vec2 q = abs(p);
    
    float radius = 0.0;
    
    if (p.x >= 0.0 && p.y >= 0.0) {        //  (top-right)
        radius = r.y;
    } else if (p.x < 0.0 && p.y >= 0.0) {  //  (top-left)
        radius = r.x;
    } else if (p.x < 0.0 && p.y < 0.0) {   //  (bottom-left)
        radius = r.w;
    } else {                                // (bottom-right)
        radius = r.z;
    }
    
    if (radius == 0.0) {
        vec2 d = q - b;
        return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);
    }
    
    vec2 cornerPos = b - vec2(radius);
    
    if (q.x > cornerPos.x && q.y > cornerPos.y) {
        vec2 cornerDist = q - cornerPos;
        float distToCorner = length(cornerDist) - radius;
        return distToCorner;
    }
    
    vec2 d = q - b;
    return max(d.x, d.y);
}

void main() {
    vec2 localPos = fragPos - position;
    vec2 halfSize = size * 0.5;
    vec2 center = halfSize;
    vec2 p = localPos - center;
    
    float outerDist = roundedRectSDF(p, halfSize, border_radius);
    
    float borderTop = border_width.x;
    float borderRight = border_width.y;
    float borderBottom = border_width.z;
    float borderLeft = border_width.w;
    
    bool hasAnyBorder = borderTop > 0.0 || borderRight > 0.0 || 
                       borderBottom > 0.0 || borderLeft > 0.0;
    
    bool hasFill = color.a > 0.001;
    
    vec2 innerHalfSize = halfSize;
    vec4 innerRadius = border_radius;
    
    if (hasAnyBorder) {
        float minHorizontalBorder = min(borderLeft, borderRight);
        float minVerticalBorder = min(borderTop, borderBottom);
        
        innerHalfSize = halfSize - vec2(minHorizontalBorder, minVerticalBorder);
        innerRadius = max(border_radius - vec4(
            borderTop, borderRight, borderBottom, borderLeft
        ), vec4(0.0));
    }
    
    float innerDist = roundedRectSDF(p, innerHalfSize, innerRadius);
    
    float alpha = 0.0;
    vec4 finalColor = vec4(0.0);
    
    if (hasAnyBorder && border_color.a > 0.001) {
        if (outerDist <= 0.0 && innerDist > 0.0) {
            alpha = border_color.a;
            finalColor = border_color;
        }
    }
    
    if (alpha == 0.0 && hasFill) {
        if (innerDist <= 0.0) {
            alpha = color.a;
            finalColor = color;
        }
    }
    
    if (outerDist > 0.0) {
        alpha *= 1.0 - smoothstep(0.0, smoothing, outerDist);
    }
    else if (innerDist > 0.0 && hasAnyBorder) {
    }
    else if (innerDist > 0.0) {
        alpha *= 1.0 - smoothstep(0.0, smoothing, innerDist);
    }
    
    if (alpha <= 0.0) {
        discard;
    }
    
    FragColor = vec4(finalColor.rgb, alpha);
}