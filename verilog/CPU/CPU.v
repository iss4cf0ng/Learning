// Your code

module CPU(clk, //POSITIVE EDGE-TRIGGER CLOCK
            rst_n, //ASYNCHRONOUS NEGATIVE EDGE RESET
            // For mem_D (data memory)
            wen_D, //0:READ, 1:WRITE, FROM DATA/STACK MEMORY
            addr_D, //ADDRESS OF DATA/STACK MEMORY
            wdata_D, //DATA TO BE WRITE TO DATA/STACK MEMORY
            rdata_D, //ADDRESS READ FROM DATA/STACK MEMORY
            // For mem_I (instruction memory (text))
            addr_I, //ADDRESS OF INSTRUCTION MEMORY -> ADDRESS OF INSTRUCTION
            rdata_I); //DATA READ FROM INSTRUCTION MEMORY -> INSTRUCTION

    input         clk, rst_n ;
    // For mem_D
    output        wen_D  ;
    output [31:0] addr_D ;
    output [31:0] wdata_D;
    input  [31:0] rdata_D;
    // For mem_I
    output [31:0] addr_I ;
    input  [31:0] rdata_I;
    
    //---------------------------------------//
    // Do not modify this part!!!            //
    // Exception: You may change wire to reg //
    reg    [31:0] PC          ;              //
    wire   [31:0] PC_nxt      ;              //
    wire          regWrite    ;              //
    wire   [ 4:0] rs1, rs2, rd;              //
    wire   [31:0] rs1_data    ;              //
    wire   [31:0] rs2_data    ;              //
    wire   [31:0] rd_data     ;              //
    //---------------------------------------//

    // Todo: other wire/reg
    integer DATA_W = 32;
    
    //Regular
    reg [6-0+1:0] opcode;
    reg [14-12+1:0] func3;
    reg [31-25+1:0] func7;
    //Immediate
    reg [31-20+1:0] imm_I_11_0; //I-type, bytes: 11 to 0
    reg [31-25+1:0] imm_S_11_5; //S-type, bytes: 11 to 5
    reg [11-7+1:0] imm_S_4_0; //S-type, bytes: 4 to 0 = uimm
    reg [31-25+1:0] imm_B_12N10_5; //B-type, byte: 12 and 10 to 5
    reg [5:0] imm_B_4_1N11;
    reg [31-12+1:0] imm_U_31_12; //U-type, byte: 31 to 12 = upimm
    reg [31-12+1:0] imm_J_20N10_1N11N19_12; //J-type, byte: 20 and 10 to 1 and 11 and 19 to 12
    //R4-Type
    reg [4:0] fs3, fs2, fs1;
    reg [1:0] func2;
    reg [31:0] addr_I_r;

    reg regWrite_r;

    //ALU
    reg [31:0] rs1_data_r, rs2_data_r, rd_data_r;

    //wire
    wire [4:0] uimm;
    wire [19:0] upimm;
    wire [31:0] imm_signExt;
    wire [31:0] BTA;

    //Assign
    assign rs2 = rdata_I[24:20];
    assign rs1 = rdata_I[19:15];
    assign rd = rdata_I[11:7];
    assign regWrite = regWrite_r;
    assign rdata_I = rd_data_r;
    
    assign rs1_data = rs1_data_r;
    assign rs2_data = rs2_data_r;
    assign rd_data = rd_data_r;

    assign addr_I = PC;

    assign uimm = imm_S_4_0;
    assign upimm = imm_U_31_12;
    assign imm_signExt = { {(21){imm_I_11_0[11]}}, imm_I_11_0[10:0] };

    assign BTA = PC + { {(32-1-12){ rdata_I[12] }}, rdata_I[11:1], 1'b0 };
    assign JTA = PC + { {(31-1-20){ rdata_I[20] }}, rdata_I[19:1], 1'b0 };

    //---------------------------------------//
    // Do not modify this part!!!            //
    reg_file reg0(                           //
        .clk(clk),                           //
        .rst_n(rst_n),                       //
        .wen(regWrite),                      //
        .a1(rs1),                            //
        .a2(rs2),                            //
        .aw(rd),                             //
        .d(rd_data),                         //
        .q1(rs1_data),                       //
        .q2(rs2_data));                      //
    //---------------------------------------//

    // Todo: any combinational/sequential circuit
    //Control
    always @(*) begin
        case (opcode)
            'd3: begin //I-type
                case (func3)
                    'b010: begin //Load word
                        rd_data_r = addr_D;
                    end
                endcase
            end
            'd19: begin //I-type
                /*
                    addi, slli, srli, srai, slti
                */
                case (func3)
                    'b000: begin //addi
                        rd_data_r = rs1_data + imm_signExt;
                    end
                    'b001: begin //slli
                        rd_data_r = rs1_data << uimm;
                    end
                    'b101: begin
                        case (func7)
                            'b0000000: begin //srli
                                rd_data_r = rs1_data >> uimm; //rd = rs1 >>> uimm
                            end
                            'b0100000: begin //srai
                                rd_data_r = rs1_data >>> uimm; //rd = rs1 >>> uimm
                            end
                        endcase
                    end
                    'b010: begin //slti
                        rd_data_r = rs1_data < imm_signExt;
                    end
                endcase
            end
            'd23: begin //U-type (auipc only)
                rd_data_r = { upimm, 12'b0 } + PC;
            end
            'd35: begin //S-type (sw only)
                addr_I_r = rs2_data;
            end
            'd51: begin //R-type
                /*
                    add, sub
                */
                case (func3)
                    'b000: begin
                        case (func7)
                            'b0000000: begin //add
                                rd_data_r = rs1_data + rs2_data; //rd = rs1 + rs2
                            end
                            'b0100000: begin //sub
                                rd_data_r = rs1_data - rs2_data; //rd = rs1 - rs2
                            end
                        endcase
                    end
                endcase
            end
            'd55: begin //U-type (lui only)
                rd_data_r = { upimm, 12'b0 };
            end
            'd99: begin //B-type
                /*
                    beq, ben, bge, blt
                */
                case (func3)
                    'b000: begin //beq
                        if (rs1_data == rs2_data) begin
                            PC = BTA;
                        end
                    end
                    'b001: begin //bne
                        if (rs1_data != rs2_data) begin
                            PC = BTA;
                        end
                    end
                    'b100: begin //blt
                        if (rs1_data < rs2_data) begin
                            PC = BTA;
                        end
                    end
                    'b101: begin //bge
                        if (rs1_data >= rs2_data) begin
                            PC = BTA;
                        end
                    end
                endcase
            end
            'd103: begin //I-type (jalr only)
                PC = rs1_data + imm_signExt;
            end
            'd111: begin //J-type (jal only)
                PC = JTA;
            end
        endcase
    end

    //Instruction Memory
    always @(*) begin
        func7 = rdata_I[31:25];

        imm_I_11_0 = rdata_I[31:20];
        imm_S_11_5 = rdata_I[31:25];

        imm_B_12N10_5[5] = rdata_I[12];
        imm_B_12N10_5[4:0] = rdata_I[10:5];

        imm_U_31_12 = rdata_I[31:12];
        
        imm_J_20N10_1N11N19_12[19] = rdata_I[20];
        imm_J_20N10_1N11N19_12[18:8] = rdata_I[10:1];
        imm_J_20N10_1N11N19_12[7] = rdata_I[11];
        imm_J_20N10_1N11N19_12[6:0] = rdata_I[19:12];

        fs3 = rdata_I[31:31-5];
        func2 = rdata_I[31-5:31-5-2];
        fs2 = rdata_I[31-5-2:31-5-2-5];
        fs1 = rdata_I[31-5-2-5:31-5-2-5-5];

        func3 = rdata_I[14:12];

        imm_S_4_0 = rdata_I[11:7];
        imm_B_4_1N11[5:1] = rdata_I[4:1];
        imm_B_4_1N11[0] = rdata_I[11];

        opcode = rdata_I[6:0];
    end

    //Sequential
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            PC <= 32'h00010000; // Do not modify this value!!!
            regWrite_r <= 0;
        end
        else begin
            PC <= PC + 4;

        end
    end
endmodule

// Do not modify the reg_file!!!
module reg_file(clk, rst_n, wen, a1, a2, aw, d, q1, q2);

    parameter BITS = 32;
    parameter word_depth = 32;
    parameter addr_width = 5; // 2^addr_width >= word_depth

    input clk, rst_n, wen; // wen: 0:read | 1:write
    input [BITS-1:0] d;
    input [addr_width-1:0] a1, a2, aw;

    output [BITS-1:0] q1, q2;

    reg [BITS-1:0] mem [0:word_depth-1];
    reg [BITS-1:0] mem_nxt [0:word_depth-1];

    integer i;

    assign q1 = mem[a1];
    assign q2 = mem[a2];

    always @(*) begin
        for (i=0; i<word_depth; i=i+1)
            mem_nxt[i] = (wen && (aw == i)) ? d : mem[i];
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            mem[0] <= 0;
            for (i=1; i<word_depth; i=i+1) begin
                case(i)
                    32'd2: mem[i] <= 32'hbffffff0;
                    32'd3: mem[i] <= 32'h10008000;
                    default: mem[i] <= 32'h0;
                endcase
            end
        end
        else begin
            mem[0] <= 0;
            for (i=1; i<word_depth; i=i+1)
                mem[i] <= mem_nxt[i];
        end
    end
endmodule

module mulDiv(clk, rst_n, valid, ready, mode, in_A, in_B, out);
    // Todo: your HW2
    parameter DATA_W = 32; //DATA WIDTH

    //INPUT
    input clk; //POSITIVE EDGE-TRIGGERED CLOCK
    input rst_n; //ASYCHRONOUS NEGATIVE EDGE RESET
    input valid; //INPUT VALID SIGNAL
    input [DATA_W-1:0] in_A; //INPUT OPERAND A
    input [DATA_W-1:0] in_B; //INPUT OPERAND B
    input [3:0] mode; //MODE
    //OUTPUT
    output ready; //OUTPUT WHEN ready = 1
    output [2*DATA_W-1:0] out; //OUTPUT DATA

    //REG
    reg [DATA_W-1:0] operand_a, operand_a_nxt;
    reg [DATA_W-1:0] operand_b, operand_b_nxt;
    reg[3:0] mod, mod_nxt;
    reg[2*DATA_W-1:0] shift_reg_r, shift_reg_w;
    reg ready_r, ready_w;
    reg [DATA_W-1:0] ctr_r;
    //WIRE
    wire [DATA_W:0] div_sub;
    wire [DATA_W-1:0] ctr_w;

    //ASSIGN
    assign out = shift_reg_r;
    assign ready = ready_r;
    assign ctr_w = ctr_r + 1;
    assign div_sub = {1'b0, shift_reg_r[2*DATA_W-2:DATA_W-1]} - operand_b;
    
    //INPUT
    always @(*) begin
        if (valid) begin
            operand_a_nxt = in_A;
            operand_b_nxt = in_B;
        end
        else begin
            operand_a_nxt = operand_a;
            operand_b_nxt = operand_b;
        end
    end

    //OUTPUT
    always @(*) begin
        case (mod) 
            'd9: begin
                if (shift_reg_r[0]) begin //LSB = 1
                    shift_reg_w = {1'b0, shift_reg_r[2*DATA_W-1:1]} + {operand_b, {(DATA_W-1){1'b0}}};
                end
                else begin //LSB = 1
                    shift_reg_w = {1'b0, shift_reg_r[2*DATA_W-1:1]};
                end
            end
            'd10: begin
                if (div_sub[DATA_W]) begin //MSB = 1
                    shift_reg_w = {shift_reg_r[2*DATA_W-2:0], 1'b0};
                end
                else begin
                    shift_reg_w = {(2*DATA_W){1'b0}};
                end
            end
            default begin
                shift_reg_w = {(2*DATA_W){1'b0}};
            end
        endcase
    end

    //FSM
    always @(*) begin
        if (ctr_r == DATA_W-1) begin //FINISH
            ready_w = 1'b1;
        end
        else begin //HAVE NOT FINSISHED, DO NEXT CYCLE
            ready_w = 1'b0;
        end
    end

    //SEQUENTIAL
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin //SET TO ZERO
            operand_a <= 0;
            operand_b <= 0;
            mod <= 0;
            ready_r <= 0;
            ctr_r <= 0;
            shift_reg_r <= 0;
        end
        else begin //UPDATE
            operand_a <= operand_a_nxt;
            operand_b <= operand_b_nxt;
            mod <= mod_nxt;
            ready_r <= ready_w;
            ctr_r <= ctr_w;
            shift_reg_r <= shift_reg_w;
        end
    end
endmodule