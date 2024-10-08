#ifndef PLAYER1_H
#define PLAYER1_H

#pragma once

#include <character_body2d.hpp>
#include <packed_scene.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

    class Player1 : public CharacterBody2D {
        GDCLASS(Player1, CharacterBody2D)

    protected:
        static void _bind_methods();

    public:
        Player1();
        ~Player1();

        void _process(double delta) override;
        void _ready() override;
        void control(double delta);

    private:
        Vector2 tank_velocity;
        float rotation_speed = 2.0;
        float speed = 200.0;
        Vector2 target_position;
        bool move_to_target = false;

        void on_click_right();
    };

}

#endif

