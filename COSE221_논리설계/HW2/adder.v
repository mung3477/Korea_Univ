module cla_gen(P, G, c0, C);
    parameter W = 4;

    //declaration
    input [W - 1: 0] P, G;
    input c0;
    output [W: 0] C;

    assign C[0] = c0;
    genvar i;
    for(i = 0; i < W; i = i + 1) begin
        assign C[i + 1] = G[i] | P[i] & C[i];
    end

endmodule

module addsub_cla(A, B, M, S, C, V);
    parameter W = 4;

    //declaration
    input [W - 1: 0] A, B;
    input M;
    output [W - 1: 0] S;
    output C, V;

    wire [W - 1: 0] P, G;
    wire[W: 0] cla;

    genvar i;
    for(i = 0; i < W; i = i + 1) begin
        assign P[i] = A[i] ^ (B[i] ^ M);
        assign G[i] = A[i] & (B[i] ^ M);
    end

    cla_gen #(.W(W)) CLAGEN(P, G, M, cla);

    for(i = 0; i < W; i = i + 1) begin
        assign S[i] = cla[i] ^ P[i];
    end

    assign C = cla[W];
    assign V = cla[W] ^ cla[W - 1];
endmodule