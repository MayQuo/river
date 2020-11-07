extends KinematicBody2D
class_name Entity
####################################################################################################
const GRAVITY: float = 80.0
const JUMP_FORCE: float = 1.4

####################################################################################################
export(String) var entity_name = "Entity"

export(float) var movement_speed: float = 100.0
export(float) var acceleration: float = 20.0

export(float) var jump_height: float = 100.0
export(int) var maximum_jump_count: int = 1
export(int) var maximum_health: int = 3

export(bool) var is_playable: bool = false
export(bool) var is_attackable: bool = true

####################################################################################################
onready var animated_sprite = $AnimatedSprite
var jump_count: int = 1
var velocity: Vector2 = Vector2()
var health: int = 3
var spawn_point: Vector2 = Vector2()
var is_moving_h = false
####################################################################################################
signal health_changed

####################################################################################################
func _ready():
	spawn_point = global_position

####################################################################################################
func attack() -> void:
	# TODO attack events
	pass
	
####################################################################################################
func jump() -> void:
	if jump_count > 0:
		jump_count = jump_count-1
		velocity.y = lerp(velocity.y, -jump_height, JUMP_FORCE)

####################################################################################################
func move(hor: float, delta: float) -> void:
	velocity.x = lerp(velocity.x, hor*movement_speed, acceleration*delta)
	is_moving_h = true
	update_flip_h(hor)

####################################################################################################
func update_flip_h(hor: float) -> void:
	if hor != 0:
		animated_sprite.scale.x = sign(hor)

####################################################################################################
func play_animation(anim: String) -> void:
	if animated_sprite.animation != anim:
		animated_sprite.play(anim)

####################################################################################################
func handle_animations() -> void:
	if velocity.y < 0:
		play_animation("jump")
	elif velocity.y > 0:
		play_animation("fall")
	elif abs(velocity.x) >= 1:
		play_animation("move")
	else:
		play_animation("idle")

####################################################################################################
func _process(delta) -> void:
	if is_on_floor() == false:
		velocity.y += GRAVITY * delta * PI
	elif velocity.y == 0:
		jump_count = maximum_jump_count
	
	if is_moving_h == false:
		velocity.x = 0
	
	# apply velocity & collision
	velocity = move_and_slide(velocity, Vector2.UP)
	velocity.x = clamp(velocity.x, -movement_speed, movement_speed)
	
	handle_animations()
	is_moving_h = false

####################################################################################################
