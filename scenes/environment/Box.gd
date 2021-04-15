extends KinematicBody2D
class_name Box

const GRAVITY = 80
var velocity: Vector2 = Vector2.ZERO
var movement_speed: float = 100.0
var acceleration: float = 20.0
var dir = 0.0

func _ready():
	pass

func _process(delta):
	if is_on_floor() == false:
		velocity.y += GRAVITY * delta * PI
	elif velocity.y > 0:
			velocity.y = 0
	velocity.x = lerp(velocity.x, movement_speed * dir, acceleration * delta)
	
	var snap = Vector2.DOWN * 4 if is_on_floor() else Vector2.ZERO
	velocity = move_and_slide_with_snap(velocity, snap, Vector2.UP)
	velocity.x = clamp(velocity.x, -movement_speed, movement_speed)

func _on_Trigger_body_entered(body):
	if not body is Entity:
		return
	(body as Entity).set_pushing(true)
	var dif = body.global_position.x - self.global_position.x
	dir = -1.0 if body.global_position.x > self.global_position.x else 1.0

func _on_Trigger_body_exited(body):
	if body is Entity:
		dir = 0.0
		(body as Entity).set_pushing(false)
