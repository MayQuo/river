extends Entity
class_name Lerow

onready var label = $Label
onready var inventory = $Inventory

export(int) var ladder_speed = 100

var roll: bool = false setget set_roll, get_roll
func set_roll(v):
	roll = v

func get_roll() -> bool:
	return roll
	
var smoke: bool = false setget set_smoke, get_smoke
func set_smoke(v):
	smoke = v

func get_smoke() -> bool:
	return smoke

func _ready():
	inventory.connect("item_changed", self, "_on_item_changed")

func _on_StateMachine_air_state_changed():
	label.text = state_machine.state.state.tag
	pass

func _on_Trigger_area_entered(area):
	if area.is_in_group("item"):
		(inventory as Inventory).add(area.collect(self))


func _on_item_changed(id, amount):
	label.text = ""
	for i in inventory.items.values():
		label.text += str(i) + ", "
	pass
