#version 120

attribute vec3 position;

uniform vec4 tx;

mat4 view_frustum(
    float angle_of_view,
    float aspect_ratio,
    float z_near,
    float z_far
) {
    return mat4(
        vec4(1.0/tan(angle_of_view), 0.0, 0.0, 0.0),
        vec4(0.0, aspect_ratio/tan(angle_of_view), 0.0, 0.0),
        vec4(0.0, 0.0, (z_far+z_near)/(z_far-z_near), 1.0),
        vec4(0.0, 0.0, -2.0*z_far*z_near/(z_far-z_near), 0.0)
    );
}

mat4 translate(float x, float y, float z)
{
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(x, y, z, 1.0)
    );
}

mat4 rotate_x(float theta)
{
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, cos(theta), sin(theta), 0.0),
        vec4(0.0, -sin(theta), cos(theta), 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

mat4 rotate_y(float theta)
{
    return mat4(
        vec4(cos(theta), 0.0, sin(theta), 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(-sin(theta), 0.0, cos(theta), 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

void main()
{
    gl_Position = view_frustum(radians(45.0), 4.0/3.0, 0.1, 1000.0)
		* (tx + vec4(position.x, position.y, position.z, 1.0));
}
