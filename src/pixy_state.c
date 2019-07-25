#include "pixy_state.h"

state_values pixy_state(state_values app_struct)
{    
    dbgOutputVal(110);
    dbgOutputLoc(PIXY_STATE_ENTER);
    
    switch(app_struct.state){
        case(INITIAL):
            dbgOutputLoc(PIXY_INITIAL);
            if(app_struct.new_byte == (char) 0x55)
                app_struct.state = SYNC;
            break;
        case(SYNC):
            dbgOutputLoc(PIXY_SYNC);
            if(app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
                app_struct.state = INITIAL;
            break;
        case(CHECK_SUM_1):
            dbgOutputLoc(PIXY_CHECKSUM1);
            if(app_struct.saved_byte == 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
            {
                app_struct.saved_byte = app_struct.new_byte;
                app_struct.state = CHECK_SUM_2;
            }
            break;
        case(CHECK_SUM_2):
            dbgOutputLoc(PIXY_CHECKSUM2);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
                app_struct.state = SIGNATURE_1;
            break;
        case(SIGNATURE_1):
            dbgOutputLoc(PIXY_SIGNATURE1);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
            {
                app_struct.saved_byte = app_struct.new_byte;
                app_struct.state = SIGNATURE_2;
            }
            break;
        case(SIGNATURE_2):
            dbgOutputLoc(PIXY_SIGNATURE2);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
            {
                if(app_struct.saved_byte == 0x01 || app_struct.saved_byte == 0x02 || app_struct.saved_byte == 0x03 || app_struct.saved_byte == 0x04) //check signatures
                {
                    app_struct.signature = app_struct.saved_byte;
                    app_struct.state = X_CENTER_1;
                }
                else
                    app_struct.state = INITIAL;
            }
            break;
        case(X_CENTER_1):
            dbgOutputLoc(PIXY_XCENTER1);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
                app_struct.state = X_CENTER_2;
            break;
        case(X_CENTER_2):
            dbgOutputLoc(PIXY_XCENTER2);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
                app_struct.state = Y_CENTER_1;
            break;
        case(Y_CENTER_1):
            dbgOutputLoc(PIXY_YCENTER1);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
                app_struct.state = Y_CENTER_2;
            break;
        case(Y_CENTER_2):
            dbgOutputLoc(PIXY_YCENTER2);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
                app_struct.state = WIDTH_1;
            break;
        case(WIDTH_1):
            dbgOutputLoc(PIXY_WIDTH1);
//            dbgOutputVal(app_struct.new_byte);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
            {
                app_struct.saved_byte = app_struct.new_byte;
                app_struct.state = WIDTH_2;
            }
            break;
        case(WIDTH_2):
            dbgOutputLoc(PIXY_WIDTH2);
//            dbgOutputVal(app_struct.new_byte);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
            {
                app_struct.pixel_width = app_struct.saved_byte;
                app_struct.state = HEIGHT_1;
            }
            break;
        case(HEIGHT_1):
            dbgOutputLoc(PIXY_HEIGHT1);
//            dbgOutputVal(app_struct.new_byte);
            if(app_struct.saved_byte == (char) 0x55 && app_struct.new_byte == 0xAA)
                app_struct.state = CHECK_SUM_1;
            else
            {
                app_struct.saved_byte = app_struct.new_byte;
                app_struct.state = HEIGHT_2;
            }
            break;
        case(HEIGHT_2):
            dbgOutputLoc(PIXY_HEIGHT2);
            app_struct.pixel_height = app_struct.saved_byte;
            if(app_struct.signature == 0x04)
                app_struct.distance = dump_distance(app_struct.pixel_width, app_struct.pixel_height);
            else
                app_struct.distance = block_distance(app_struct.pixel_width, app_struct.pixel_height);                
            app_struct.state = INITIAL;
            break;
        default:
            break;
    }
    
    dbgOutputLoc(PIXY_STATE_EXIT);
    
    dbgOutputVal(150);
    return app_struct;
}