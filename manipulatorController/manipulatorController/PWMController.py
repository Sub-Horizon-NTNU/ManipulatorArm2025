import RPi.GPIO as GPIO


class PWMController():
    def __init__(self):
        self.armMin = 700
        self.armMax = 2300
        self.minWristSpeed = 1125
        self.maxWristSpeed = 1725
        self.lightMin = 1050
        self.lightMax = 1900
        self.armServoPin = 17
        self.wristServoPin = 22
        self.lightPin = 27

        GPIO.setmode(GPIO.BCM)
        GPIO.setup(armServoPin, GPIO.OUT)
        GPIO.setup(wristServoPin, GPIO.OUT)
        GPIO.setup(lightPin, GPIO.OUT)
        armOut = GPIO.PWM(armServoPin, 50)
        wristOut = GPIO.PWM(wristServoPin, 50)
        lightOut = GPIO.PWM(lightPin, 50)
        armOut.start(armMin)
        wristOut.start(minWristSpeed + ((maxWristSpeed - minWristSpeed)/2))
        lightOut.start(lightMin)

    def changeArmSpeed(self, speed):
        wristSpeed = (minWristSpeed + ((maxWristSpeed - minWristSpeed)/2)) + (3*speed)
        setPWM(wristServoPin/20000 * 100, wristSpeed)

    def changeArmAngle(self, angle):
        armPosition = armMin + 32 * angle
        setPWM(armServoPin/20000 * 100, armPosition)

    def changeLightStrength(self, lightStrength):
        lightOut = lightMin + lightStrength * 8.5
        setPWM(lightPin/20000 * 100, lightOut)

    def setPWM(self, pwmOut, value):
        dutyCycle = value/20000 * 100