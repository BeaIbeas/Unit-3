int sWAITING = 0;
int sMOVING  = 1;
int sSAFETY  = 3;

int currentState = sWAITING; //why do we need to define current state instead of using sWAITING directly?????

int eyeL = 0;
int eyeR = 0;

int pinLeftEye = 8;
int pinRightEye = 7;

int motionTime = 1200;

void setup() {
}

void move_bot(int dir, int msec) { //what is dir???????????
    // here we still have to implement the actual motion code
    currentState = sMOVING;
}

void look_araound() {
    eyeL = analogRead( pinLeftEye );
    eyeR = analogRead( pinRightEye );

    // NOTE: the reading will probably be a bit chaotic, and might be 
    // different for each sensor, so we need to normalize them.
}

void i_am_safe_now() {
    currentState = sSAFETY;
}

void loop() {

    look_around();


    // if both eyes read below 20% light then our current state is sWAITING
    // if reading on eyeL is 20% great than reading on eyeR then move to R (for X steps) transititon to stte sMOVING
    // if reading on eyeR is 20% great than reading on eyeL then move to L (for X steps) transititon to stte sMOVING
    // if I am moving and I reach a spot when the light readings are again below 20% then I go into state sWAITING

    if( (currentState == sWAITING) && (eyeL > eyeR) ) {
        move_bot(Right, motionTime);
    } else ( eyeR > eyeL ) {
        move_bot(Left, motionTime);
    }

    if( (currentState == sWAITING) && ( eyeR < lowLightThreshold ) ) {
        i_am_safe_now();
    }
}
// if ((currentState == sMOVING) && (eyeL > eyeR))
        move_bot (Right, motionTime);  // to define that while it's moving should go L or R ??????
        } else (eyeR > eyeL) {
          move_bot (Left, motionTime);
        }
        
    if (currentState == sMOVING) && (eyeL & eyeR > lowLightThreshold)) {
        i_am_safe_now(); // to define that it's moving but should stop ??????
        
        
      
