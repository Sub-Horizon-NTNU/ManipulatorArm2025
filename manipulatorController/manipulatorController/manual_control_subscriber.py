import RPi.GPIO as GPIO
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64, Int32

class PWMController:
    def __init__(self):
        # GPIO setup
        GPIO.setmode(GPIO.BCM)
        self.armMin = 700
        self.armMax = 2300
        self.minWristSpeed = 1125
        self.maxWristSpeed = 1725
        self.lightMin = 1050
        self.lightMax = 1900
        self.armServoPin = 17
        self.wristServoPin = 22
        self.lightPin = 27

        GPIO.setup(self.armServoPin, GPIO.OUT)
        GPIO.setup(self.wristServoPin, GPIO.OUT)
        GPIO.setup(self.lightPin, GPIO.OUT)
        
        self.armOut = GPIO.PWM(self.armServoPin, 50)
        self.wristOut = GPIO.PWM(self.wristServoPin, 50)
        self.lightOut = GPIO.PWM(self.lightPin, 50)
        
        self.armOut.start(self.armMin)
        mid_wrist = self.minWristSpeed + ((self.maxWristSpeed - self.minWristSpeed)/2)
        self.wristOut.start(mid_wrist)
        self.lightOut.start(self.lightMin)

    def changeArmSpeed(self, speed):
        wrist_speed = (self.minWristSpeed + 
                      ((self.maxWristSpeed - self.minWristSpeed)/2)) + (3*speed)
        self._setPWM(self.wristOut, wrist_speed)

    def changeArmAngle(self, angle):
        arm_position = self.armMin + 32 * angle
        self._setPWM(self.armOut, arm_position)

    def _setPWM(self, pwm_out, value):
        duty_cycle = (value / 20000) * 100
        pwm_out.ChangeDutyCycle(duty_cycle)

class ManualControlSubscriber(Node):
    def __init__(self):
        super().__init__('manual_control_subscriber')
        self.pwmController = PWMController()  # Initialize here
        
        # Angle subscription
        self.angle_subscription = self.create_subscription(
            Float64,
            'manualControlAngle',
            self.angle_callback,
            10)
        
        # Speed subscription
        self.speed_subscription = self.create_subscription(
            Int32,
            'manualControlSpeed',
            self.speed_callback,
            10)
        
        self.get_logger().info("Subscriber Initialized")

    def angle_callback(self, msg):
        self.get_logger().info(f'Angle: {msg.data}')
        self.pwmController.changeArmAngle(msg.data)

    def speed_callback(self, msg):
        self.get_logger().info(f'Speed: {msg.data}')
        self.pwmController.changeArmSpeed(msg.data)

def main(args=None):
    rclpy.init(args=args)
    subscriber = ManualControlSubscriber()
    try:
        rclpy.spin(subscriber)
    finally:
        subscriber.destroy_node()
        rclpy.shutdown()
        GPIO.cleanup()

if __name__ == '__main__':
    main()