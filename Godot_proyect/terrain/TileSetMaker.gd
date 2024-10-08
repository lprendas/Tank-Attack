extends Node2D

var tile_size = Vector2(128, 128)
@onready var texture = $Sprite2D.texture

func _ready():
	var tex_width = int(texture.get_width() / tile_size.x)
	var tex_height = int(texture.get_height() / tile_size.y)
	var ts = TileSet.new()
	var atlas_source = TileSetAtlasSource.new()
	
	atlas_source.set_texture(texture)
	atlas_source.set_texture_region_size(Vector2i(tile_size.x, tile_size.y)) 
	atlas_source.set_margins(Vector2i(0, 0))
	atlas_source.set_separation(Vector2i(0, 0))
	atlas_source.set_use_texture_padding(true)

	for x in range(tex_width):
		for y in range(tex_height):
			var coords = Vector2i(x, y)
			atlas_source.create_tile(coords)
			
	ts.add_source(atlas_source)
	
	ResourceSaver.save(ts, "res://terrain/terrain_tiles.tres")
