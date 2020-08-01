module huffman_decoder(x, y, clk, reset);
input x;
output [2 : 0] y;
input clk;
input reset;

reg [3 : 0] cur_state;
reg [3 : 0] next_state;
parameter sNull = 4'b0000, sA = 4'b0001, sB = 4'b0010, sC = 4'b0011, sD = 4'b0100, sE = 4'b0101, sF = 4'b0110, s1 = 4'b0111, s2 = 4'b1000, s3 = 4'b1001, s4 = 4'b1010;

initial begin
    cur_state = sNull;
end

//sequential logic for state trainsition
always @ (posedge clk or posedge reset) begin
    //initialize variables to prevent unexpected latches
    cur_state = 4'b0000;

    if(reset == 0) begin
        cur_state <= next_state;
    end
    else begin
        cur_state <= sNull;
    end
end

//combinational logic for next state
always @ (*) begin
        case (cur_state)
        sNull: if(x == 0) next_state = sA; else next_state = s1;
        sA: if(x == 0) next_state = sA; else next_state = s1;
        sB: if(x == 0) next_state = sA; else next_state = s1;
        sC: if(x == 0) next_state = sA; else next_state = s1;
        sD: if(x == 0) next_state = sA; else next_state = s1;
        sE: if(x == 0) next_state = sA; else next_state = s1;
        sF: if(x == 0) next_state = sA; else next_state = s1;
        s1: if(x == 0) next_state = s2; else next_state = s3;
        s2: if(x == 0) next_state = sC; else next_state = sB;
        s3: if(x == 0) next_state = s4; else next_state = sD;
        s4: if(x == 0) next_state = sF; else next_state = sE;
        default: next_state = 4'bxxxx;
        endcase
end

assign y[2] = cur_state[2] & (~cur_state[1] | ~cur_state[0]);
assign y[1] = (~cur_state[3] & ~cur_state[2] & cur_state[1]) | (cur_state[2] & cur_state[1] & ~cur_state[0]);
assign y[0] = (~cur_state[3] & ~cur_state[2] & cur_state[0]) | (cur_state[2] & ~cur_state[1] & cur_state[0]);

endmodule