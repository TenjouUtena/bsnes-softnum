use std::path::Path;



fn main() {
    cc::Build::new()
        .file("gb/Core/apu.c")
        .file("gb/Core/camera.c")
        .file("gb/Core/debugger.c")
        .file("gb/Core/rumble.c")
        .file("gb/Core/display.c")
        .file("gb/Core/gb.c")
        .file("gb/Core/joypad.c")
        .file("gb/Core/mbc.c")
        .file("gb/Core/memory.c")
        .file("gb/Core/printer.c")
        .file("gb/Core/random.c")
        .file("gb/Core/rewind.c")
        .file("gb/Core/save_state.c")
        .file("gb/Core/sgb.c")
        .file("gb/Core/sm83_cpu.c")
        .file("gb/Core/sm83_disassembler.c")
        .file("gb/Core/symbol_hash.c")
        .file("gb/Core/timing.c")

        .compile("bsnes")
}
