extends Node2D
class_name Stage

onready var player: Entity = find_node("Lerow", true, true)
onready var player_controller: PlayerController = $PlayerController
onready var camera: Camera2D =  $Camera2D
onready var camera_zoom: AnimationPlayer = $Camera2D/Zoom
onready var healthbar: HBoxContainer = $UI/Healthbar

var heart_container = preload("res://scenes/ui/HeartContainer.tscn")
var heart_full = preload("res://textures/ui/heart_full.png")
var heart_empty = preload("res://textures/ui/heart_empty.png")

onready var camera_target = player_controller
var camera_player_speed = 5.0
var camera_cinematic_speed = 2.0
var camera_speed

func _ready() -> void:
	player_controller.player = player
	generate_healthbar_container()
	camera_speed = camera_player_speed
	

func _process(delta: float) -> void:
	camera.position = lerp(camera.position, camera_target.position, camera_speed * delta)
	healthbar_container_beating()

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
