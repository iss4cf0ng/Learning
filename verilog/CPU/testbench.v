// The testbench feeds initial instruction and data and checks the result of data memory.d

`timescale 1 ns/10 ps

`define CYCLE 10       // Do not change this value!!!
`define END_CYCLE 5000 // You can modify your maximum cycles

`include "CPU.v"
`include "memory.v"
`define SIZE_TEXT 100  // You can change the size
`define SIZE_DATA 32  // You can change the size
`define SIZE_STACK 64 // You can change the size

`ifdef arithmetic
    `define INIT_JUMP 0
    `define MEM_TEXT "./arithmetic/arithmetic_text.txt"
    `define MEM_DATA "./arithmetic/arithmetic_data.txt"
    `define MEM_DATA_ANS "./arithmetic/arithmetic_data_ans.txt"
`endif

`ifdef sort
    `define INIT_JUMP 1
    `define MEM_TEXT "./sort/sort_text.txt"
    `define MEM_DATA "./sort/sort_data.txt"
    `define MEM_DATA_ANS "./sort/sort_data_ans.txt"
`endif

`ifdef gcd
    `define INIT_JUMP 1
    `define MEM_TEXT "./gcd/gcd_text.txt"
    `define MEM_DATA "./gcd/gcd_data.txt"
    `define MEM_DATA_ANS "./gcd/gcd_data_ans.txt"
`endif

module Final_tb;

    reg         clk, rst_n ;
    
    wire        mem_wen_D  ;
    wire [31:0] mem_addr_D ;
    wire [31:0] mem_wdata_D;
    wire [31:0] mem_rdata_D;
    
    wire [31:0] mem_addr_I ;
    wire [31:0] mem_rdata_I;

    reg  [31:0] mem_data_ans [0:`SIZE_DATA-1];
    reg  [31:0] mem_text_offset;
    reg  [31:0] mem_data_offset;
    reg  [31:0] mem_stack_offset;

    integer i;
    
    integer eof;
    reg eof_find;

    integer error_num;
    
    CPU chip0(
        .clk            (clk),
        .rst_n(rst_n),
        // for mem_D
        .wen_D          (mem_wen_D),
        .addr_D         (mem_addr_D),
        .wdata_D        (mem_wdata_D),
        .rdata_D        (mem_rdata_D),
        // for mem_I
        .addr_I         (mem_addr_I),
        .rdata_I        (mem_rdata_I));
    
    memory #(.word_depth(`SIZE_TEXT)) mem_text(
        .clk(clk),
        .rst_n(rst_n),
        .wen(1'b0),
        .a(mem_addr_I),
        .d(32'd0),
        .q(mem_rdata_I),
        .offset(mem_text_offset));

    memory #(.word_depth(`SIZE_DATA)) mem_data(
        .clk(clk),
        .rst_n(rst_n),
        .wen(mem_wen_D),
        .a(mem_addr_D),
        .d(mem_wdata_D),
        .q(mem_rdata_D),
        .offset(mem_data_offset));

    memory #(.word_depth(`SIZE_STACK)) mem_stack(
        .clk(clk),
        .rst_n(rst_n),
        .wen(mem_wen_D),
        .a(mem_addr_D),
        .d(mem_wdata_D),
        .q(mem_rdata_D),
        .offset(mem_stack_offset));

    // Initialize the data memory
    initial begin
        $fsdbDumpfile("Final.fsdb");            
        $fsdbDumpvars(0,Final_tb,"+mda");

        $display("------------------------------------------------------------\n");
        $display("START!!! Simulation Start .....\n");
        $display("------------------------------------------------------------\n");
        
        clk = 1;
        rst_n = 1'b1;
        mem_text_offset = 32'h00010000; // attention: instruction memory starts from 0x00010000
        mem_stack_offset = 32'hbffffff4 - `SIZE_STACK*4; // attention: stack memory starts from 0xbfffffbc
        eof_find = 0;

        $readmemh (`MEM_TEXT, mem_text.mem); // initialize data in mem_I

        for (i=0; i<`SIZE_TEXT; i=i+1) begin
            if ((mem_text.mem[i] === 32'bx) && !eof_find) begin
                eof = mem_text_offset + i*4;
                eof_find = 1;
            end
        end

        mem_data_offset = eof + ((`INIT_JUMP) ? 0 : 8);

        #(`CYCLE*0.5) rst_n = 1'b0;
        #(`CYCLE*2.0) rst_n = 1'b1;
                
        for (i=0; i<32; i=i+1) begin
            mem_text.mem[i] = 32'h00_00_00_13;
        end
        $readmemh (`MEM_TEXT, mem_text.mem); // initialize data in mem_I
        
        for (i=0; i<`SIZE_DATA; i=i+1) begin
            mem_data.mem[i] = 0;
            mem_data_ans[i] = 0;
        end
        $readmemh (`MEM_DATA, mem_data.mem); // initialize data in mem_D
        $readmemh (`MEM_DATA_ANS, mem_data_ans); // initialize data in mem_D
        
    end

    initial begin
        #(`CYCLE*`END_CYCLE)
        
        $display("============================================================\n");
        $display("Simulation time is longer than expected.");
        $display("The test result is .....FAIL :(\n");
        $display("============================================================\n");
        
        $finish;
    end
    
    always @(negedge clk) begin
        if (mem_addr_I == eof) begin
            error_num = 0;
            for (i=0; i<`SIZE_DATA; i=i+1) begin
                if (mem_data.mem[i] !== mem_data_ans[i]) begin
                    if (error_num == 0)
                        $display("Error!");
                    error_num = error_num + 1;
                    $display("  Addr = 0x%8h  Correct ans: 0x%8h  Your ans: 0x%8h", mem_data.mem_addr[i], mem_data_ans[i], mem_data.mem[i]);
                end
            end
            if (error_num > 0) begin
                $display(" ");
                $display("============================================================\n");
                $display("There are total %4d errors in the data memory", error_num);
                $display("The test result is .....FAIL :(\n");
                $display("============================================================\n");
            end
            else begin
                $display("============================================================\n");
                $display("Success!");
                $display("The test result is .....PASS :)\n");
                $display("============================================================\n");
            end
            $finish;
        end
    end
        
    always #(`CYCLE*0.5) clk = ~clk;
        
endmodule
