extends Node2D
class_name Stage

onready var player = find_node("Lerow", true, true)
onready var player_controller = $PlayerInputHandler
onready var camera: Camera2D =  $Camera2D
onready var camera_zoom: AnimationPlayer = $Camera2D/Zoom
onready var healthbar: HBoxContainer = $UI/Healthbar
onready var inventory_ui: InventoryUI = $UI/InventoryUI
var next_sticky = null
var swapped_player = false

var heart_container = preload("res://scenes/ui/HeartContainer.tscn")
var heart_full = preload("res://textures/ui/heart_full.png")
var heart_empty = preload("res://textures/ui/heart_empty.png")

onready var camera_target = player_controller
var camera_player_speed = 5.0
var camera_cinematic_speed = 2.0
var camera_speed

func _ready() -> void:
	player_controller.entity = player
	generate_healthbar_container()
	camera_speed = camera_player_speed

func _process(delta: float) -> void:
	camera.position = lerp(camera.position, camera_target.position, camera_speed * delta)
	healthbar_container_beating()
	
	if Input.is_action_just_pressed("ui_accept"):
		if next_sticky and swapped_player == false:
			swapped_player = true
			player_controller.entity = next_sticky
		else:
			swapped_player = false
			player_controller.entity = player
	
	if Input.is_action_just_pressed("inventory"):
		inventory_ui.visible = !inventory_ui.visible

func _on_Lerow_health_changed():
	generate_healthbar_container()
	update_healthbar_container()

func update_healthbar_container():
	var children = healthbar.get_children()
	for n in range(0, len(children)):
		if n > player.health-1:
			children[n].texture = heart_empty
		else:
			children[n].texture = heart_full

func healthbar_container_beating():	
	if player.health <= 1:
		for n in healthbar.get_children():
			var anim_player = n.get_node("AnimationPlayer")
			anim_player.play("beat")
	
func generate_healthbar_container():
	var amount = len(healthbar.get_children())
	
	while(amount > player.maximum_health):
		healthbar.remove_child(healthbar.get_children().back())
	
	for n in range(amount, player.maximum_health):
		var heart = heart_container.instance()
		if n > player.health-1:
			heart.texture = heart_empty
		else:
			heart.texture = heart_full
		
		healthbar.add_child(heart)

func _on_Forest01_cinematic_action_start(target):
	camera_target = target
	camera_speed = camera_cinematic_speed
	player.is_playable = false
	camera_zoom.play("zoom_out")

func _on_Forest01_cinematic_action_finished():
	camera_target = player_controller
	camera_speed = camera_player_speed
	player.is_playable = true
	camera_zoom.play("zoom_in")

func _on_StickyGreen_body_entered(body, other):
	if body.is_in_group("lerow"):
		next_sticky = other

func _on_StickyGreen_body_exited(body, other):
	if body.is_in_group("lerow"):
		next_sticky = null


func _on_Item2_item_picked_up(actor):
	$StickyGreen/ThiefLabel.text = "Du Dieb! Die Kräuter gehören mir!"
