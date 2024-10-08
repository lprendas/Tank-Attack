#include "Player1.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Player1::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("control", "delta"), &Player1::control);
	//ClassDB::bind_method(D_METHOD("on_click_right"), &Player1::on_click_right);
}

Player1::Player1()
{
}

Player1::~Player1()
{
}

void Player1::_process(double delta)
{
    /*control(delta);
    if (move_to_target) {
        Vector2 direction = (target_position - get_position()).normalized();
        tank_velocity = direction * speed * delta;
        set_position(get_position() + tank_velocity);

        if (get_position().distance_to(target_position) < 5.0) {
            move_to_target = false;
            tank_velocity = Vector2();
        }
    }*/
}

void Player1::_ready()
{
	//Input::get_singleton()->connect("mouse_button_down", Callable(this, "on_click_right"));
}

void Player1::control(double delta)
{
    /*
    int rot_dir = 0;
    if (Input::get_singleton()->is_action_pressed("turn_right")) {
        rot_dir += 1;
    }
    else {
        UtilityFunctions::printerr("La acción 'right' no existe o no está presionada.");
    }
    if (Input::get_singleton()->is_action_pressed("turn_left")) {
        rot_dir -= 1;
    }
    else {
        UtilityFunctions::printerr("La acción 'left' no existe o no está presionada.");
    }
    set_rotation(get_rotation() + rotation_speed * rot_dir * delta);

    tank_velocity = Vector2();
    if (Input::get_singleton()->is_action_pressed("forward")) {
        tank_velocity = Vector2(speed, 0).rotated(get_rotation());
    }
    else {
        UtilityFunctions::printerr("La acción 'forward' no existe o no está presionada.");
    }
    if (Input::get_singleton()->is_action_pressed("back")) {
        tank_velocity = Vector2(-speed / 2, 0).rotated(get_rotation());
    }
    else {
        UtilityFunctions::printerr("La acción 'back' no existe o no está presionada.");
    }
    set_position(get_position() + tank_velocity * delta);*/
}

void Player1::on_click_right()
{
    /*if (Input::get_singleton()->is_action_just_pressed("click_right")) {
        target_position = get_global_mouse_position();
        move_to_target = true;
    }*/
}
