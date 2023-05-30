#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_scene(Scene* scene,Camera* camera)
{
    scene->rotation = 0.0;
    scene->key_roation = 0.0;
    scene->light = 0.0;
    

    load_model(&(scene->skeleton), "assets/models/skeletons.obj");
    
	load_model(&(scene->chair), "assets/models/chair.obj");
    scene->texture_id = load_texture("assets/textures/floor.jpg");


    load_model(&(scene->bookcase), "assets/models/bookcase.obj");
    scene->texture_bookcase = load_texture("assets/textures/bookcase.jpg");

    load_model(&(scene->haunted), "assets/models/houseandfloor.obj");
    scene->texture_house = load_texture("assets/textures/bookcase.jpg");

    load_model(&(scene->candle), "assets/models/CandleStick.obj");
    scene->texture_key = load_texture("assets/textures/candle.jpg");

    load_model(&(scene->table), "assets/models/table.obj");
    scene->texture_table = load_texture("assets/textures/table_col.jpg");

    load_model(&(scene->movingBook.MoveKey), "assets/models/book.obj");
	scene->texture_key = load_texture("assets/textures/help.jpg");
	

    scene->texture_help = load_texture("assets/textures/help.jpg");


    scene->material.ambient.red = 1;
    scene->material.ambient.green = 1;
    scene->material.ambient.blue = 1;

    scene->material.diffuse.red = 1; 
    scene->material.diffuse.green = 1; 
    scene->material.diffuse.blue = 1;

    scene->material.specular.red = 1;
    scene->material.specular.green = 1;
    scene->material.specular.blue = 1;

    scene->material.shininess = 50; 

}

void set_lighting(const Scene* scene)
{
   float b;
    b = scene->light / 255 ;
    float ambient_light[] = { b, b, b, b };
    float diffuse_light[] = { b, b, b, b };
    float specular_light[] = { b, b, b, b };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}


void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, Camera* camera,double elapsed_time)
{
    scene->movingBook.position.x = camera->position.x;
    scene->movingBook.position.y = camera->position.y;
   

    scene->rotation += 0.5 ;
    scene->key_roation += 3;
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
    draw_origin();
    draw_skeleton(scene);
    draw_house(scene);
    draw_table(scene);
    draw_key(scene);
    draw_chair(scene);
    draw_bookcase(scene);
    draw_key_move(scene);
}


void draw_chair(const Scene* scene){
    glPushMatrix();
    glTranslatef(1.5, 1, 0.35);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->rotation, 0, 1, 0);
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    set_material(&(scene->material));
    draw_model(&(scene->chair));
    glPopMatrix();
}

void draw_skeleton(const Scene* scene){
    glPushMatrix();
    glTranslatef(4, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.05, 0.05, 0.05);
    set_material(&(scene->material));
    draw_model(&(scene->skeleton));
    glPopMatrix();
}

void draw_bookcase(const Scene* scene){
    glPushMatrix();
    glTranslatef(-0.5, 2, 0.05);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    glBindTexture(GL_TEXTURE_2D, scene->texture_bookcase);
    set_material(&(scene->material));
    draw_model(&(scene->bookcase));
    glPopMatrix();
}


void draw_house(const Scene* scene){
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.15, 0.15, 0.15);
    glBindTexture(GL_TEXTURE_2D, scene->texture_house);
    set_material(&(scene->material));
    draw_model(&(scene->haunted));
    glPopMatrix();
}


void draw_table(const Scene* scene){
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->texture_table);
    set_material(&(scene->material));
    draw_model(&(scene->table));
    glPopMatrix();
}

void draw_key(const Scene* scene){
    glPushMatrix();
    glTranslatef(0, -1, 0.25);
    glRotatef(90, 1, 0, 0);
    glScalef(0.05, 0.05, 0.05);
    glBindTexture(GL_TEXTURE_2D, scene->texture_key);
    set_material(&(scene->material));
    draw_model(&(scene->candle));
    glPopMatrix();
}

void draw_key_move(const Scene* scene){
    float x,y;
    x = scene->movingBook.position.x + 0.1;
    y = scene->movingBook.position.y + 0; 
    glBindTexture(GL_TEXTURE_2D, scene->texture_key);
    glPushMatrix();
    glTranslatef(x, y, 0.9);
    glRotatef(90, 1, 0, 0);
    glScalef(0.02, 0.02, 0.02);
    draw_model(&(scene->movingBook));
    glPopMatrix();
}

void Key_up(Scene* scene, int a, Camera* camera){
    int c = a;
    if(c == 1){
        scene->movingBook.position.x = camera->position.x;
        scene->movingBook.position.y = camera->position.y;
        scene->movingBook.position.z = camera->position.z;
    }
}

void set_sun_brightness_inc(Scene* scene, float b)
{
   scene->light += b;

    if(scene->light > 255.0){
        scene->light = 255.0;
    }
    if(scene->light < 0.0){
        scene->light = 0.0;
    }
}

void show_help(GLuint help_texture) {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, help_texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3d(-2, 1.5, -3);
        glTexCoord2f(1, 0);
        glVertex3d(2, 1.5, -3);
        glTexCoord2f(1, 1);
        glVertex3d(2, -1.5, -3);
        glTexCoord2f(0, 1);
        glVertex3d(-2, -1.5, -3);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}