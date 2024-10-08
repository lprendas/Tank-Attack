extends "res://scenes/Tank.gd"

func control(delta):
	$Turret.look_at(get_global_mouse_position())
