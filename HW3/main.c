#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "vector.h"

static const float PI = 3.14159265358979323846f;
static const float EPSILON = 1e-6f;
static const int OUTPUT_PRECISION = 15;

static void print_vector3(const char *label, Vector3 value, int precision)
{
    printf("%s = (%.*f, %.*f, %.*f)\n", label, precision, value.x, precision, value.y, precision, value.z);
}

static void print_vector2(const char *label, Vector2 value, int precision)
{
    printf("%s = (%.*f, %.*f)\n", label, precision, value.x, precision, value.y);
}

static void print_scalar(const char *label, float value, int precision)
{
    printf("%s = %.*f\n", label, precision, value);
}

static bool isVisible2D(Vector2 view_vector, Vector2 target_vector)
{
    float dot_product = vector2_dot(view_vector, target_vector);
    float view_length = vector2_length(view_vector);
    float target_length = vector2_length(target_vector);

    if (view_length == 0.0f || target_length == 0.0f)
    {
        return false;
    }

    float cos_angle = dot_product / (view_length * target_length);
    if (cos_angle > 1.0f)
    {
        cos_angle = 1.0f;
    }
    else if (cos_angle < -1.0f)
    {
        cos_angle = -1.0f;
    }

    float angle = acosf(cos_angle) * (180.0f / PI);

    return angle < 20.0f;
}

static bool getIntersection2D(Vector2 ray_start, Vector2 ray_dir,
                              Vector2 p1, Vector2 p2, Vector2 *hit_point)
{
    float vx = p2.x - p1.x;
    float vy = p2.y - p1.y;

    float delta_x = p1.x - ray_start.x;
    float delta_y = p1.y - ray_start.y;

    float det = -ray_dir.x * vy + ray_dir.y * vx;

    if (fabsf(det) < EPSILON)
    {
        return false;
    }

    float t = (-delta_x * vy + delta_y * vx) / det;
    float u = (ray_dir.x * delta_y - ray_dir.y * delta_x) / det;

    if (t > EPSILON && u >= 0.0 && u <= 1.0)
    {
        if (hit_point != NULL)
        {
            hit_point->x = ray_start.x + (t * ray_dir.x);
            hit_point->y = ray_start.y + (t * ray_dir.y);
        }
        return true;
    }

    return false;
}

static Vector2 getFacingNormal2D(Vector2 p1, Vector2 p2, Vector2 incident_dir)
{
    double wx = p2.x - p1.x;
    double wy = p2.y - p1.y;
    
    Vector2 n1 = {-wy, wx};
    Vector2 n2 = {wy, -wx};
    
    n1 = vector2_normalize(n1);
    n2 = vector2_normalize(n2);
    
    if (vector2_dot(incident_dir, n1) < 0.0f)
    {
        return n1;
    }
    return n2;
}

static float getHitAngle2D(Vector2 incident_dir, Vector2 p1, Vector2 p2)
{
    Vector2 wall_vec = {p2.x - p1.x, p2.y - p1.y};
    
    Vector2 dir_norm = vector2_normalize(incident_dir);
    Vector2 wall_norm = vector2_normalize(wall_vec);
    
    float cos_theta = fabsf(vector2_dot(dir_norm, wall_norm));
    
    if (cos_theta > 1.0f)
    {
        cos_theta = 1.0f;
    }
    
    return acosf(cos_theta) * (180.0f / PI);
}

static Vector2 reflect2D(Vector2 incident_dir, Vector2 normal)
{
    float dot = vector2_dot(incident_dir, normal);
    
    return (Vector2){
        .x = incident_dir.x - (2.0f * dot * normal.x),
        .y = incident_dir.y - (2.0f * dot * normal.y),
    };
}

int main(void)
{
    // Task 1
    puts("--- Task 1 ---");
    Vector3 a = vector3_add((Vector3){5.6f, -1.2f, -4.5f}, (Vector3){1.1f, 2.2f, 5.1f});
    Vector3 b = vector3_add((Vector3){4.3f, 0.2f, -1.5f}, (Vector3){-1.1f, 3.0f, 1.2f});
    Vector3 c = vector3_add((Vector3){5.4f, -1.1f, 2.9f}, (Vector3){-3.6f, 0.5f, -1.8f});
    Vector3 d = vector3_add((Vector3){2.7f, -0.9f, 3.8f}, (Vector3){-1.4f, 2.5f, -1.2f});
    Vector3 e = vector3_scale((Vector3){-2.1f, 3.7f, 0.5f}, -1.1f);
    Vector3 f = vector3_add((Vector3){6.6f, -1.2f, 3.2f}, (Vector3){2.6f, 2.6f, 2.6f});
    Vector3 g = vector3_add((Vector3){2.5f, -1.8f, 3.4f}, vector3_scale((Vector3){-1.2f, 2.9f, -0.6f}, 0.7f));
    Vector3 h = vector3_add((Vector3){-3.1f, 4.2f, -2.7f}, vector3_scale((Vector3){1.8f, -2.4f, 0.9f}, -1.5f));
    float i = vector3_dot((Vector3){3.1f, -2.4f, 1.7f}, (Vector3){-0.8f, 1.4f, -2.3f});
    float j = vector3_dot((Vector3){4.2f, 0.9f, -3.5f}, (Vector3){-2.1f, 3.3f, 0.4f});

    print_vector3("a", a, OUTPUT_PRECISION);
    print_vector3("b", b, OUTPUT_PRECISION);
    print_vector3("c", c, OUTPUT_PRECISION);
    print_vector3("d", d, OUTPUT_PRECISION);
    print_vector3("e", e, OUTPUT_PRECISION);
    print_vector3("f", f, OUTPUT_PRECISION);
    print_vector3("g", g, OUTPUT_PRECISION);
    print_vector3("h", h, OUTPUT_PRECISION);
    print_scalar("i", i, OUTPUT_PRECISION);
    print_scalar("j", j, OUTPUT_PRECISION);

    // Task 2
    puts("\n--- Task 2 ---");
    Vector2 player_relative_position = {-1.0f, +0.0f};
    Vector2 enemy_relative_position = {+1.0f, +0.0f};

    Vector2 player_view_vectors[6] = {
        {+1.0f, +0.0f},
        {+0.0f, +1.0f},
        {+1.0f, +0.0f},
        {+1.0f, +0.0f},
        {+1.0f, +0.0f},
        {+0.9f, +0.1f},
    };

    Vector2 enemy_view_vectors[6] = {
        {-1.0f, +0.0f},
        {+1.0f, +0.0f},
        {-0.9f, +0.4f},
        {-0.8f, -0.6f},
        {-1.0f, +0.1f},
        {-0.9f, -0.1f},
    };

    const char labels[6] = {'a', 'b', 'c', 'd', 'e', 'f'};

    puts("\nPlain vectors (a and b):");
    for (int idx = 0; idx < 6; ++idx)
    {
        char a_label[] = {'a', '_', labels[idx], '\0'};
        char b_label[] = {'b', '_', labels[idx], '\0'};

        print_vector2(a_label, player_view_vectors[idx], OUTPUT_PRECISION);
        print_vector2(b_label, enemy_view_vectors[idx], OUTPUT_PRECISION);

        bool player_can_see_enemy = isVisible2D(player_view_vectors[idx], enemy_relative_position);
        bool enemy_can_see_player = isVisible2D(enemy_view_vectors[idx], player_relative_position);

        printf("visible_%c = %s\n", labels[idx], player_can_see_enemy && enemy_can_see_player ? "true\n" : "false\n");
    }

    // Task 3
    puts("\n--- Task 3 ---");
    Vector2 bullet_start = {-2.0f, +2.0f}; // S
    Vector2 bullet_direction = {+1.0f, -1.0f}; // d

    Vector2 wall_A_start = {-3.0f, -1.0f}; // A
    Vector2 wall_A_end = {+4.0f, +1.0f}; // B

    Vector2 wall_B_start = {+4.0f, +1.0f}; // B
    Vector2 wall_B_end = {-1.0f, +3.0f}; // C

    Vector2 hit_point_A; // Where bullet hits wall A
    getIntersection2D(bullet_start, bullet_direction, wall_A_start, wall_A_end, &hit_point_A);

    Vector2 normal_wall_A = getFacingNormal2D(wall_A_start, wall_A_end, bullet_direction);
    Vector2 reflected_dir_A = reflect2D(bullet_direction, normal_wall_A);
    float hit_angle_A = getHitAngle2D(bullet_direction, wall_A_start, wall_A_end);

    print_vector2("Hit Point A", hit_point_A, OUTPUT_PRECISION);
    print_vector2("Reflected Dir A", reflected_dir_A, OUTPUT_PRECISION);
    print_scalar("Hit Angle A", hit_angle_A, OUTPUT_PRECISION);
    print_vector2("Normal A", normal_wall_A, OUTPUT_PRECISION);

    Vector2 hit_point_B; // Where bullet hits wall B
    getIntersection2D(hit_point_A, reflected_dir_A, wall_B_start, wall_B_end, &hit_point_B);

    Vector2 normal_wall_B = getFacingNormal2D(wall_B_start, wall_B_end, reflected_dir_A);
    Vector2 reflected_dir_B = reflect2D(reflected_dir_A, normal_wall_B);
    float hit_angle_B = getHitAngle2D(reflected_dir_A, wall_B_start, wall_B_end);

    print_vector2("\nHit Point B", hit_point_B, OUTPUT_PRECISION);
    print_vector2("Reflected Dir B", reflected_dir_B, OUTPUT_PRECISION);
    print_scalar("Hit Angle B", hit_angle_B, OUTPUT_PRECISION);
    print_vector2("Normal B", normal_wall_B, OUTPUT_PRECISION);

    return 0;
}