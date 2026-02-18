module ALU  #(
    parameter DATA_W = 32
)
(
    input           clk, //POSITIVE EDGE-TRIGGERED CLOCK
    input           rst_n, //ASYNCHRONOUS NEGATIVE EDGE RESET
    input           valid, //INPUT VALID SIGNAL
    input   [31:0]  in_A, //INPUT OPERAND A
    input   [31:0]  in_B, //INPUT OPERAND B
    input   [3:0]   mode, //MODE
    output          ready, //OUTPUT WHEN ready = 1
    output  [63:0]  out_data //OUTPUT DATA
);

//WIRE CANNOT BE IN ALWAYS BLOCK
//r: reg, w: wire

// PARAMETERS
    //FSM BASED ON OPERATION CYCLE
    parameter S_IDLE = 2'd0;
    //parameter S_SINGLE_CYCLE_OP = 2'd1;
    parameter S_MULTI_CYCLE_OP = 2'd1;

// ===============================================
//                    wire & reg
// ===============================================
    //REGISTER
    //STATE
    reg [1:0] state, state_nxt;
    //REGISTER, OPERAND AND OPERAND IN NEXT STATE
    reg [DATA_W-1:0] operand_a, operand_a_nxt; 
    reg [DATA_W-1:0] operand_b, operand_b_nxt;
    reg [3:0] mod, mod_nxt; //MODE
    //READY SIGNAL
    reg ready_r, ready_w;
    //COUNTER -> FSM
    reg [DATA_W-1:0] ctr_r; //COUNTER READ
    wire [DATA_W-1:0] ctr_w; //COUNTER WRITE
    //SHIFT REG
    reg [2*DATA_W-1:0] shift_reg_r, shift_reg_w; //SHIFT REGISTER READ, WRITE

    //WIRE
    wire [DATA_W-1:0] sum, dif, lshift, rshift, op_and, op_or, op_eq, op_gt, op_xor;
    wire [DATA_W:0] div_sub;
    
    //OPERATION, WIRE ASSIGNMENT
    assign out_data = shift_reg_r;
    assign ready = ready_r;
    assign ctr_w = (state == S_MULTI_CYCLE_OP) ? ctr_r + 1 : 0;
    
    assign sum = operand_a + operand_b; //A+B
    assign dif = operand_a - operand_b; //A-B
    assign op_and = operand_a & operand_b;
    assign op_or = operand_a | operand_b;
    assign op_eq = operand_a == operand_b;
    assign op_gt = operand_a > operand_b;
    assign op_xor = operand_a ^ operand_b;
    assign l_shift = operand_a << (operand_b); //LEFT SHIFT
    assign r_shift = $unsigned($signed(operand_a) >>> operand_b); //RIGHT SHIFT
    assign div_sub = {1'b0, shift_reg_r[2*DATA_W-2:DATA_W-1]} - operand_b;

// ===============================================
//                   combinational
// ===============================================

//LOAD INPUT
always @(*) begin
    if (valid) begin //VALID INPUT DATA
        operand_a_nxt = in_A;
        operand_b_nxt = in_B;
        mod_nxt = mode;
    end
    else begin
        operand_a_nxt = operand_a;
        operand_b_nxt = operand_b;
        mod_nxt = mod;
    end
end

//OUTPUT
always @(*) begin
    case(state)
        S_IDLE: begin
            if (valid && (mode == 4'd9 || mode == 4'd10)) begin
                shift_reg_w = {{DATA_W{1'b0}}, in_A};
            end
            else if (valid && (mode != 4'd9 && mode != 4'd10)) begin
                case (mod)
                4'd0: begin //ADD
                    /*
                        THERE ARE 2 CASE OF OVERFLOW OF ADD
                            1: POSITIVE + POSITIVE = NEGATIVE
                            2: NEGATIVE + NEGATIVE = POSITIVE
                    */
                    case ({operand_a[DATA_W-1], operand_b[DATA_W-1], sum[DATA_W-1]})
                        3'b001:  shift_reg_w = {{DATA_W{1'b0}}, 1'b0, {(DATA_W-1){1'b1}}}; // pos + pos = neg, overflow
                        3'b110:  shift_reg_w = {{DATA_W{1'b0}}, 1'b1, {(DATA_W-1){1'b0}}}; // neg + neg = pos, underflow
                        default: shift_reg_w = {{DATA_W{1'b0}}, sum};
                    endcase
                end
                4'd1: begin //SUB
                    /*
                        THERE ARE TWO CASE OF OVERFLOW OF SUB
                            1: POSITIVE - NEGATIVE = NEGATIVE
                            2: NEGATIVE - POSITIVE = POSITIVE
                    */
                    case ({operand_a[DATA_W-1], operand_b[DATA_W-1], dif[DATA_W-1]})
                        3'b011: shift_reg_w = {{DATA_W{1'b0}}, 1'b0, {(DATA_W-1){1'b1}}}; //CASE 1
                        3'b100: shift_reg_w = {{DATA_W{1'b0}}, 1'b1, {(DATA_W-1){1'b0}}}; //CASE 2
                        default: shift_reg_w = {{DATA_W{1'b0}}, dif}; //NO OVERFLOW, PUT dif INTO shift_reg_w
                    endcase
                end
                4'd2: begin //AND
                    shift_reg_w = {{DATA_W{1'b0}}, op_and};
                end
                4'd3: begin //OR
                    shift_reg_w = {{(DATA_W){1'b0}}, op_or};
                end
                4'd4: begin //XOR
                    shift_reg_w = {{(DATA_W){1'b0}}, op_xor};
                end
                4'd5: begin //EQUAL
                    shift_reg_w = {{(DATA_W-1){1'b0}}, op_eq};
                end
                4'd6: begin //GREATER THAN
                    /*
                    integer sign_a = operand_a[31];
                    integer sign_b = operand_b[31];
                    if (sign_a == 1'b0 && sign_b == 1'b1) begin //POSITIVE > NEGATIVE => STORE 1
                        shift_reg_w = {{DATA_W{1'b0}}, 1'b1};
                    end
                    else if (sign_a == 1'b1 && sign_a == 1'b0) begin
                        shift_reg_w = {{DATA_W{1'b0}}, 1'b0}; //NEGATIVE < POSITIVE => STORE 0
                    end
                    else begin //OTHERWISE, JUST COMPARE THEM
                        shift_reg_w = {{DATA_W{1'b0}}, operand_a > operand_b};
                    end
                    */
                    case ({operand_a[DATA_W-1], operand_b[DATA_W-1]})
                        2'b01: shift_reg_w = {{(2*DATA_W-1){1'b0}}, 1'b1}; //POSITIVE > NEGATIVE => STORE 1
                        2'b10: shift_reg_w = {{(2*DATA_W){1'b0}}}; //NEGATIVE < POSITIVE => STORE 0
                        default: shift_reg_w = {{(DATA_W){1'b0}}, op_gt}; //OTHERWISE
                    endcase
                end
                'd7: begin //SHIFT RIGHT LOGICAL
                    shift_reg_w = {{DATA_W{1'b0}}, rshift};
                end
                'd8: begin //SHIFT LEFT LOGICAL
                    shift_reg_w = {{DATA_W{1'b0}}, lshift};
                end
                default: begin
                    shift_reg_w = {(2*DATA_W){1'b0}};
                end
            endcase
            end
        end
        S_MULTI_CYCLE_OP: begin
            case (mod)
                'd9: begin //MUL
                    if (shift_reg_r[0]) begin
                        shift_reg_w = {1'b0, shift_reg_r[2*DATA_W-1:1]} + {operand_b, {(DATA_W-1){1'b0}}};
                    end
                    else begin
                        shift_reg_w = {1'b0, shift_reg_r[2*DATA_W-1:1]};
                    end
                end
                'd10: begin //DIV
                    if (div_sub[DATA_W]) begin
                        shift_reg_w = {shift_reg_r[2*DATA_W-2:0], 1'b0};
                    end
                    else begin
                        shift_reg_w = {div_sub[DATA_W-1:0], shift_reg_r[DATA_W-2:0], 1'b1};
                    end
                end
                default: shift_reg_w = {(2*DATA_W){1'b0}};
                endcase
        end
        default: begin
            shift_reg_w = shift_reg_r;
        end
    endcase
end

//FSM
/*
    TODO:
    FINISH FSM
*/
always @(*) begin
    case (state)
    S_IDLE: begin
        if (!valid) begin //NO OPERATION
            state_nxt = S_IDLE;
            ready_w = 1'b0;
        end
        else if (mode == 4'd9 || mode == 4'd10) begin //MULTIPLE CYCLE: MULTIPLICATION, DIVISION
            state_nxt = S_MULTI_CYCLE_OP;
            ready_w = 1'b0;
        end
        else begin //SINGLE CYCLE OPERATION: AND, OR, SUB, XOR, 
            state_nxt = S_IDLE;
            ready_w = 1'b1;
        end
        //ready_w = 1'b0;
    end
    S_MULTI_CYCLE_OP: begin
        if (ctr_r == DATA_W-1) begin //FINISH
            state_nxt = S_IDLE;
            ready_w = 1'b1;
        end
        else begin //NEXT MUL CYCLE
            state_nxt = S_MULTI_CYCLE_OP;
            ready_w = 1'b0;
        end
    end
    default: begin //NEXT STATE
        state_nxt = state;
        ready_w = 1'b0;
    end
    endcase
end

// ===============================================
//                    sequential
// ===============================================
/*
    TODO:
    FINISH SEQUENTIAL
*/
always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        state <= S_IDLE;
        operand_a <= 0;
        operand_b <= 0;
        mod <= 0;
        ready_r <= 0;
        ctr_r <= 0;
        shift_reg_r <= 0;
    end else begin
        state <= state_nxt;
        operand_a <= operand_a_nxt;
        operand_b <= operand_b_nxt;
        mod <= mod_nxt;
        ready_r <= ready_w;
        ctr_r <= ctr_w;
        shift_reg_r <= shift_reg_w;
    end
end

endmodule