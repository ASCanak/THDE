int main( void ){
	WDT -> WDT_MR = WDT_MR_WDDIS;

    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c );
    auto f1 = hwlib::font_default_8x8();
    auto w1 = hwlib::part(oled, hwlib::xy(0, 0), hwlib::xy(128, 32));
    auto scherm = hwlib::terminal_from(w1, f1);

    ir_Encoder my_Encoder = ir_Encoder();
    OLED screen = OLED(scl,sda);    
    gameControl gameCtrl = gameControl(my_Encoder, screen);
    parameterControl paramCtrl = parameterControl(gameCtrl);
    ir_Decoder test2 = ir_Decoder(paramCtrl, gameCtrl);
    KeypadTaak test3 = KeypadTaak(paramCtrl, screen);

    rtos::run();
}