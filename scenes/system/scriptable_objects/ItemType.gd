extends Resource
class_name ItemType

export(String) var name: String
export(Texture) var texture: Texture
export(String) var description: String
export(Array) var values
var id: int

func _init(_id, _name, _texture, _description, _values):
	name = _name
	texture = _texture
	description = _description
	values = _values
	id = _id
