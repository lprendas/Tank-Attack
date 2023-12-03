shader_type canvas_item;

uniform float speed : hint_range(0, 10) = 1.0;
uniform float amplitude : hint_range(0, 1) = 0.1; // Ajusta según sea necesario
uniform float brightness : hint_range(0, 2) = 1.0;

void vertex() {
    // Aplicar deformación de izquierda a derecha
    VERTEX.x += sin(VERTEX.y * amplitude + TIME * speed) * amplitude;
	COLOR.rgb += cos(TIME * speed + VERTEX.y) * amplitude;
}

void fragment() {
    // Ajustar brillo
    COLOR.rgb *= brightness;
}