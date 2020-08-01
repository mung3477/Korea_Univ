// Moore model FSM (see Fig. 5.19)
module One_detector (
output [1:0] s_out,
output [1:0] n_out,
output y,
input x_in, clock, reset 
);
reg [1:0] state;
reg [1:0] next_state;

parameter S0 = 2'b00, S1 = 2'b01, S2 = 2'b10, S3 = 2'b11;

//sequential logic for state transition
always @ (posedge clock, negedge reset)
if (reset == 0) state <= S0; // Initialize to state S0 
else state <= next_state;

//combinational logic for next state
always @(*)
begin
	case (state)
	S0: if (x_in) next_state = S1; else next_state = S0;
	S1: if (x_in) next_state = S2; else next_state = S0;
	S2: if (x_in) next_state = S3; else next_state = S0;
	S3: if (x_in) next_state = S3; else next_state = S0;
	default: next_state = 2'bxx;
	endcase
end

assign s_out = state; // Output of flip-flops
assign y = state[0] & state[1];

assign n_out[1] = (state[1]|state[0])&x_in;
assign n_out[0] = (state[1]|~state[0])&x_in;

endmodule



module TOP;

wire [1:0] cur_AB;
wire [1:0] nxt_AB;
wire y;

reg x,CLOCK,t_reset;

One_detector O1(cur_AB,nxt_AB,y,x,CLOCK,t_reset);

initial #200 $finish;

initial begin
t_reset = 0; CLOCK = 0; #5 t_reset = 1;
repeat (16)
#5 CLOCK = ~CLOCK;
end

initial begin
x = 0; #12 x = 1;
repeat (8)
//#10 x = ~x;
#30 x = ~x;
end

initial
begin
$dumpfile("test_output.vcd");
$dumpvars;
end

endmodule
