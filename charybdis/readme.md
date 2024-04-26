# Charybdis (3x5) default keymap

> [!NOTE]
> QMK Firmware needs to be pointed at https://github.com/Bastardkb/bastardkb-qmk and checkout `bkb-master`!
>
> I did a dumb and fried my serial pin and had to bodge it to a different pin.  The `info.json` overrides this mapping to GP14 on Line 20.

> :bulb: Have a look at the [`via` keymap](../via) for a more feature-rich layout.

The Charydbis (3x5) default keymap is inspired from the original [Dactyl Manuform](../../../../../handwired/dactyl_manuform) default keymap.

This layout supports RGB matrix. However, due to space constraints on the MCU, only a limited number of effect can be enabled at once. Look at the `config.h` file and enable your favorite effect.
