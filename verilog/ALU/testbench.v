`timescale 1ns/1ps
`define CYCLE       10.0
`define MAX_CYCLE   1000
`define IN_DELAY    2.0
`define OUT_DELAY   2.0

// p3, p4, p5 are for hidden patterns
`ifdef p1
    `define Inst_I  "./pattern/pattern1.dat"
    `define Inst_O  "./pattern/golden1.dat"
    `define PAT_NUM 22
`elsif p2
    `define Inst_I  "./pattern/pattern2.dat"
    `define Inst_O  "./pattern/golden2.dat"
    `define PAT_NUM 55
`elsif p3
    `define Inst_I  "./pattern/pattern3.dat"
    `define Inst_O  "./pattern/golden3.dat"
    `define PAT_NUM 55
`elsif p4
    `define Inst_I  "./pattern/pattern4.dat"
    `define Inst_O  "./pattern/golden4.dat"
    `define PAT_NUM 55
`elsif p5
    `define Inst_I  "./pattern/pattern5.dat"
    `define Inst_O  "./pattern/golden5.dat"
    `define PAT_NUM 55
`else 
    `define Inst_I  "./pattern/pattern0.dat"
    `define Inst_O  "./pattern/golden0.dat"
    `define PAT_NUM 11
`endif

module testbench;
    parameter INST_W = 4;
    parameter DATA_W = 32;
    integer                  i = 0;
    integer                  j = 0;
    integer                  error = 0;
    integer                  count = 0;

    // inout port
    reg                     i_clk = 0;
    reg                     i_rst_n = 1;
    reg                     i_valid = 0;
    reg     [DATA_W-1:0]    i_data_a = 0;
    reg     [DATA_W-1:0]    i_data_b = 0;
    reg     [INST_W-1:0]    i_inst = 0;

    wire                    o_ready;
    wire    [DATA_W*2-1:0]  o_data;

    reg                         next = 1;
    reg [2*DATA_W+INST_W-1:0]   inst_idata [0:`PAT_NUM-1];
    reg [DATA_W*2-1:0]          inst_odata [0:`PAT_NUM-1];
    reg [DATA_W-1:0]            test_inA;
    reg [DATA_W-1:0]            test_inB;
    reg [INST_W-1:0]            test_inst;
    reg [DATA_W*2-1:0]          test_outD;

    ALU u_alu (
        .clk          (i_clk      ),
        .rst_n        (i_rst_n    ),
        .valid        (i_valid    ),
        .in_A         (i_data_a   ),
        .in_B         (i_data_b   ),
        .mode         (i_inst     ),
        .ready        (o_ready    ),
        .out_data     (o_data     )
    );

    always #(`CYCLE/2.0) i_clk = ~i_clk; 

    always @(posedge i_clk) begin
        #(`IN_DELAY);
        i_valid = (next && i_rst_n) ? $random : 0;
        if (i_valid) begin
            i_data_b = inst_idata[i][DATA_W-1:0];
            i_data_a = inst_idata[i][DATA_W+:DATA_W];
            i_inst   = inst_idata[i][2*DATA_W+:INST_W];
            i = i + 1;
            next = 0;
        end else begin
            i_data_b = 0;
            i_data_a = 0;
            i_inst   = 0;
        end
    end

    always @(posedge i_clk) begin
        #(`IN_DELAY);
        if (i_valid || (count==33)) begin
            count = 0;
        end else if (!next) begin
            count = count + 1;
        end
    end

    initial begin
        #(`IN_DELAY);
        i_rst_n = 0;
        #(2.0 * `CYCLE);
        i_rst_n = 1;
    end

    initial begin
        j = 0;
        error = 0;
        while (j < `PAT_NUM) begin
            @(posedge i_clk);
            #(`CYCLE - `OUT_DELAY);
            test_inst = inst_idata[j][2*DATA_W+:INST_W];

            if ((test_inst == 4'd9 || test_inst == 4'd10) && o_ready) begin
                if (count == 33) begin
                    test_inB  = inst_idata[j][DATA_W-1:0];
                    test_inA  = inst_idata[j][DATA_W+:DATA_W];
                    test_outD = inst_odata[j][2*DATA_W-1:0];
                    if (test_outD !== o_data) begin
                        $display (
                            "Test[%d]: Error! Mode=%0h, A=%0h, B=%0h, Golden=%0h, Yours=%0h", 
                            j, test_inst, test_inA, test_inB, test_outD, o_data
                        );      
                        error = error+1;        
                    end 
                    else begin
                        $display (
                            "Test[%d]: Correct! Mode=%0h, A=%0h, B=%0h, Golden=%0h, Yours=%0h", 
                            j, test_inst, test_inA, test_inB, test_outD, o_data
                        );
                    end
                end
                else begin
                    $display (
                            "Test[%d]: Error! Mode=%0h, You do not output at the checking time", 
                            j, test_inst
                    );
                    error = error+1; 
                end
                j = j+1;
                next = 1;
            end
            else if (test_inst <= 4'd8 && o_ready) begin
                if (count == 1) begin
                    test_inB  = inst_idata[j][DATA_W-1:0];
                    test_inA  = inst_idata[j][DATA_W+:DATA_W];
                    test_outD = inst_odata[j][2*DATA_W-1:0];

                    if (test_outD !== o_data) begin
                        $display (
                            "Test[%d]: Error! Mode=%0h, A=%0h, B=%0h, Golden=%0h, Yours=%0h", 
                            j, test_inst, test_inA, test_inB, test_outD, o_data
                        );      
                        error = error+1;
                    end 
                    else begin
                        $display (
                            "Test[%d]: Correct! Mode=%0h, A=%0h, B=%0h, Golden=%0h, Yours=%0h", 
                            j, test_inst, test_inA, test_inB, test_outD, o_data
                        );
                    end
                end
                else begin
                    $display (
                            "Test[%d]: Error! Mode=%0h, You do not output at the checking time", 
                            j, test_inst
                    );
                    error = error+1;
                end

                j = j+1;
                next = 1;
            end
        end

        $display("Pattern: ", `Inst_I);

        if(error == 0) begin
            $display("----------------------------------------------");
            $display("-                 ALL PASS!                  -");
            $display("----------------------------------------------");
        end else begin
            $display("----------------------------------------------");
            $display("  Wrong! Total error: %d                      ", error);
            $display("----------------------------------------------");
        end
        $finish;
    end

    initial begin
        # (`MAX_CYCLE * `CYCLE);
        $display("----------------------------------------------");
        $display("Latency of your design is over 100000 cycles!!");
        $display("----------------------------------------------");
        $finish;
    end
    
    initial begin
        $readmemb(`Inst_I, inst_idata);
        $readmemb(`Inst_O, inst_odata);
    end

    initial begin
       $fsdbDumpfile("alu.fsdb");
       $fsdbDumpvars(0, testbench, "+mda");
    end

endmodule
