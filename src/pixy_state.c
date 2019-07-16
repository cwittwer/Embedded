#include "pixy_state.h"

state_values pixy_state(state_values app_struct)
{
    dbgOutputLoc(PIXY_STATE_ENTER);
    
    int combined = 0x0000;
    switch(app_struct.state){
        case(INITIAL):
            dbgOutputLoc(PIXY_INITIAL);
            if(app_struct.new_byte = 0x55)
                app_struct.state = SYNC;
            break;
        case(SYNC):
            dbgOutputLoc(PIXY_SYNC);
            if(app_struct.new_byte = 0xaa)
                app_struct.state = CHECK_SUM_1;
            else
                app_struct.state = INITIAL;
            break;
        case(CHECK_SUM_1):
            dbgOutputLoc(PIXY_CHECKSUM1);
            app_struct.state = CHECK_SUM_2;
            break;
        case(CHECK_SUM_2):
            dbgOutputLoc(PIXY_CHECKSUM2);
            app_struct.state = SIGNATURE_1;
            break;
        case(SIGNATURE_1):
            dbgOutputLoc(PIXY_SIGNATURE1);
            app_struct.saved_byte = app_struct.new_byte;
            app_struct.state = SIGNATURE_2;
            dbgOutputVal(app_struct.new_byte);
            break;
        case(SIGNATURE_2):
            dbgOutputLoc(PIXY_SIGNATURE2);
            combined = combine_bytes(app_struct.new_byte, app_struct.saved_byte);
            dbgOutputVal(app_struct.new_byte);
            //saved_byte has to equal 0x78
            if(combined == 0x0001 || combined == 0x0002 || combined == 0x0004) //check signatures
                app_struct.state = X_CENTER_1;
            else
                app_struct.state = INITIAL;
            break;
        case(X_CENTER_1):
            dbgOutputLoc(PIXY_XCENTER1);
            app_struct.state = X_CENTER_2;
            break;
        case(X_CENTER_2):
            dbgOutputLoc(PIXY_XCENTER2);
            app_struct.state = Y_CENTER_1;
            break;
        case(Y_CENTER_1):
            dbgOutputLoc(PIXY_YCENTER1);
            app_struct.state = Y_CENTER_2;
            break;
        case(Y_CENTER_2):
            dbgOutputLoc(PIXY_YCENTER2);
            app_struct.state = WIDTH_1;
            break;
        case(WIDTH_1):
            dbgOutputLoc(PIXY_WIDTH1);
            app_struct.saved_byte = app_struct.new_byte;
            app_struct.state = WIDTH_2;
            break;
        case(WIDTH_2):
            dbgOutputLoc(PIXY_WIDTH2);
            app_struct.pixel_width = combine_bytes(app_struct.new_byte, app_struct.saved_byte);
            app_struct.state = HEIGHT_1;
            break;
        case(HEIGHT_1):
            dbgOutputLoc(PIXY_HEIGHT1);
            app_struct.saved_byte = app_struct.new_byte;
            app_struct.state = HEIGHT_2;
            break;
        case(HEIGHT_2):
            dbgOutputLoc(PIXY_HEIGHT2);
            app_struct.pixel_height = combine_bytes(app_struct.new_byte, app_struct.saved_byte);
            app_struct.distance = block_distance(app_struct.pixel_width, app_struct.pixel_height);
            app_struct.state = INITIAL;
            break;
        default:
            break;
    }
    
    dbgOutputLoc(PIXY_STATE_EXIT);
    
    return app_struct;
}