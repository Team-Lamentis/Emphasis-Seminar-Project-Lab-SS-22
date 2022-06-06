library ieee ;
use ieee.std_logic_1164.all ;


entity myFSM is
 port (rst, clk, e: in bit;
 q: out bit);
 end entity myFSM;
 architecture behavioral of myFSM is
 type state is (S0, S1, S2); 
 signal current_state, next_state: state;
begin

state_memory: process(clk, rst)
 begin
if rst = '1' then
 current_state <= S0;
 elsif (clk = '1' and clk'event) then
 current_state <= next_state;
 end if;
 end process;

input_comb: process(current_state, e)
begin
 case current_state is
when S0 => if e = '1' then
next_state <= S0;
else next_state <= S1;
end if;
when S1 => if e = '1' then
next_state <= S2;
else next_state <= S1;
end if;



	when S2 => if e = '1' then
next_state <= S0;
else next_state <= S0;
end if;

 end case;
end process;

output_comb: process(current_state, e)
begin
 case current_state is
when S2 => if e = '0' then
q <= '1';
else q <= '1';
end if;
when others => q <= '0';
 end case;
end process;
end architecture;
