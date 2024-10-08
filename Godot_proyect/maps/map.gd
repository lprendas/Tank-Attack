extends Node2D

# Referencias a los nodos importantes
var ground_tile_map : TileMap = null
var player2 : Node2D
var selected_tank : Node = null  # Tanque actualmente seleccionado
var map : Node = null

# Importar los métodos desde C++
@export var map_cpp_node : Map  # Nodo de C++ ya instanciado

func _ready():
	player2 = get_node("Ground/Player2")
	map = get_node("/root/Map")  # Cambiar la ruta para que apunte al nodo Map
	if map == null:
		print("Error: Nodo 'Map' no encontrado")
	ground_tile_map = $Ground  # Referencia a Ground
	player2 = ground_tile_map.get_node("Player2")  # Referencia a Player2
	selected_tank = null  # Ningún tanque seleccionado al inicio
	if map_cpp_node == null:
		print("Error: Nodo map_cpp_node no asignado")
	else:
		print("map_cpp_node asignado correctamente.")
	print("Player2 encontrado: ", player2 != null)
	print("Ground TileMap encontrado: ", ground_tile_map != null)
	var tank1 = player2.get_node("Tank1")
	var tank2 = player2.get_node("Tank2")
	print("Tank1 encontrado: ", tank1 != null)
	print("Tank2 encontrado: ", tank2 != null)
	print(ground_tile_map.get_used_rect())

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_LEFT and event.is_pressed():
			handle_left_click()
		elif event.button_index == MOUSE_BUTTON_RIGHT and event.is_pressed():
			handle_right_click()

func handle_left_click():
	var mouse_position = get_global_mouse_position()
	var tanks = [player2.get_node("Tank1"), player2.get_node("Tank2")]  # Obtener referencias a Tank1 y Tank2
	var clicked_tank : CharacterBody2D = null

	# Detectar si se ha hecho clic dentro del área del tanque
	for tank in tanks:
		var tank_position = tank.get_global_position()
		var tank_shape = tank.get_node("CollisionShape2D")
		
		if tank_shape and tank_shape.shape is RectangleShape2D:
			var rect_extents = tank_shape.shape.extents
			var rect = Rect2(tank_position - rect_extents, rect_extents * 2)

			# Verificamos si la posición del mouse está dentro del área del tanque
			if rect.has_point(mouse_position):
				clicked_tank = tank
				break

	if clicked_tank != null:
		selected_tank = clicked_tank  # Seleccionar el tanque
		print("Tanque seleccionado: ", selected_tank.name)
	else:
		selected_tank = null
		print("No hay tanque seleccionado.")

func handle_right_click():
	if selected_tank != null and map != null:
		print("Posición del tanque en píxeles: ", selected_tank.global_position)
		var mouse_position = get_global_mouse_position()
		print("Posición del ratón en píxeles: ", mouse_position)

		# Convertir correctamente la posición global del ratón al espacio local del TileMap
		var local_mouse_position = ground_tile_map.to_local(mouse_position)

		# Obtener las coordenadas de la celda basadas en la posición local
		var grid_position = ground_tile_map.local_to_map(local_mouse_position)

		# Obtener las coordenadas del tanque y convertirlas correctamente
		var tank_global_position = selected_tank.get_global_position()
		var local_tank_position = ground_tile_map.to_local(tank_global_position)
		var tank_grid_position = ground_tile_map.local_to_map(local_tank_position)

		# Ahora deberías tener grid_position y tank_grid_position correctas
		print("Posición del ratón en celdas: ", grid_position)
		print("Posición del tanque en celdas: ", tank_grid_position)

		var path = map_cpp_node.movementPlayer1(tank_grid_position, grid_position)

		if path.size() > 0:
			for i in range(path.size()):
				var current_cell = path[i]
				var world_pos = ground_tile_map.map_to_local(current_cell)
				selected_tank.global_position = world_pos
				if selected_tank.has_node("Body"):
					selected_tank.get_node("Body").global_position = world_pos
				if selected_tank.has_node("Turret"):
					selected_tank.get_node("Turret").global_position = world_pos
				selected_tank.queue_redraw()
				await get_tree().create_timer(0.1).timeout
		else:
			print("No hay camino disponible para el tanque.")
