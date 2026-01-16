#version 330 core
out vec4 FragColor;

uniform vec3 color;
uniform vec2 size;
uniform vec4 borderRadius;
uniform vec2 position;
uniform float smoothing; // Можно передавать из программы

in vec2 fragPos;

// SDF функция для прямоугольника с закругленными углами
float roundedRectSDF(vec2 p, vec2 b, vec4 r) {
    // Для каждого квадранта используем свой радиус
    float radius = 0.0;
    
    // Определяем квадрант (с учетом вашей системы координат)
    if (p.x > 0.0 && p.y > 0.0) {      // Bottom-right
        radius = r.z;
    } else if (p.x > 0.0 && p.y <= 0.0) { // Top-right
        radius = r.y;
    } else if (p.x <= 0.0 && p.y > 0.0) { // Bottom-left
        radius = r.w;
    } else {                             // Top-left
        radius = r.x;
    }
    
    // Если радиус 0, это обычный прямоугольник
    if (radius == 0.0) {
        vec2 d = abs(p) - b;
        return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);
    }
    
    // Для закругленных углов
    vec2 q = abs(p) - b + radius;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - radius;
}

void main() {
    // Центр прямоугольника
    vec2 center = position + size * 0.5;
    vec2 p = fragPos - center;
    vec2 b = size * 0.5;
    
    // Вычисляем расстояние до фигуры
    float distance = roundedRectSDF(p, b, borderRadius);
    
    // Плавный переход с использованием smoothing
    float smoothingFactor = 1.0; // или uniform переменная
    
    // Используем smoothstep для антиалиасинга
    float alpha = 1.0 - smoothstep(0.0, smoothingFactor, distance);
    
    if (alpha <= 0.0) {
        discard;
    }
    
    FragColor = vec4(color, alpha);
}