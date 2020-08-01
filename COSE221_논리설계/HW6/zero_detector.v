//zero detector module

module zero_detector(
    output [1 : 0] present_state,
    output y,
    input x,
    input clock,
    input reset
);

reg [1 : 0] cur_state = 2'b00;
reg [1 : 0] next_state;
parameter S0 = 2'b00, S1 = 2'b01, S2 = 2'b10;

//sequential logic
always @ (posedge clock or negedge reset) begin
    if(reset == 0) begin
        cur_state <= S0;
    end
    else begin
        cur_state <= next_state;
    end
end

//combinational logic for next state
always @ (*) begin
    next_state[1] = (~x & cur_state[0]) + (~x & cur_state[1]);
    next_state[0] = (~x & ~cur_state[1] & ~cur_state[0]);
end

assign y = cur_state[1];
assign present_state = cur_state;


endmodule

//You don't need to modify module TOP
module TOP;

wire [1 : 0] p_state;
wire y_out;

reg x_in;
reg CLOCK;
reg t_reset;

//create instance of zero_detector
zero_detector Z1(p_state, y_out, x_in, CLOCK, t_reset);

//simulate for 200 time units
initial #200 $finish;

//create reset signal
initial begin
    t_reset = 0;
    #3 t_reset = 1;
end

//create clock signal
initial begin
    CLOCK = 0;
    repeat (40)
    #5 CLOCK = ~CLOCK; //at every 5 time units
end

//create input signal
initial begin
    x_in = 0; #12 x_in = 1;
    repeat (8)
    #20 x_in = ~x_in;
end

//create dumpfile to view waveforms
initial begin
    $dumpfile("h2_dump.vcd");
    $dumpvars;
end

endmodule