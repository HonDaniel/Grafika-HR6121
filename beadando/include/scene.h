#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"

#include <obj/model.h>

typedef struct Key
{
    Model MoveKey;
    GLuint texture_keyid;
    vec3 position;
    vec3 rotation;
} Key;


typedef struct Scene
{
    Model chair;
    Model haunted;
    Model skeleton;
    Model bookcase;
    Model table;
    Model candle;
    Key movingBook;
    Material material;
    GLuint texture_id;
    GLuint texture_house;
    GLuint texture_bookcase;
    GLuint texture_table;
    GLuint texture_key;
    GLuint texture_help;
	GLuint texture_skeleton;
    float light;
    float rotation;
    float key_roation;
    bool is_help_visible;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene, Camera* camera);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, Camera* camera, double elapsed_time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw a chair.
 */
void draw_chair(const Scene* scene);

void draw_skeleton(const Scene* scene);

void draw_bookcase(const Scene* scene);

void draw_house(const Scene* scene);

void draw_table(const Scene* scene);

void draw_key(const Scene* scene);

void draw_key_move(const Scene* scene);

void Key_up(Scene* scene, int a, Camera* camera);

void set_sun_brightness_inc(Scene* scene, float b);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();


#endif /* SCENE_H */
