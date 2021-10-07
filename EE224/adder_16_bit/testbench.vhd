entity testbench is
end testbench;
architecture tb of testbench is
signal x, y : bit_VECTOR(15 downto 0); -- inputs
signal ot :bit_VECTOR(15 downto 0); -- output
signal ctr0,ctr1,car,zero : bit;
	
	component ALU is
		port(s0,s1: in bit;
			a: in bit_VECTOR(15 downto 0);
			b: in bit_VECTOR(15 downto 0);
			o: out bit_VECTOR(15 downto 0);
			z,carry: out bit);
	end component;

begin
-- Connecting test bench signals with ALU.vhd
dut_instance: ALU

port map (s0 => ctr0,s1 => ctr1,a => x, b => y, o => ot,z => zero,carry => car);

process-- inputs
	begin
		ctr0 <= '0';
		ctr1 <= '0';
		x <= "0000000000101101"; -- 45 dif = 0000000000010111, sum = 0000000001000011
		y <= "0000000000010110"; -- 22
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '0';
		x <= "0000000000101101";
		y <= "0000000000010110";
		wait for 0.1 ns;
		ctr0 <= '0';
		ctr1 <= '1';
		x <= "0000000000101101";
		y <= "0000000000010110";
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '1';
		x <= "0000000000101101";
		y <= "0000000000010110";
		wait for 0.1 ns;
		
		ctr0 <= '0';
		ctr1 <= '0';
		x <= "0000000000000000";
		y <= "0000000000000000";
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '0';
		x <= "0000000000000000"; 
		y <= "0000000000000000"; 
		wait for 0.1 ns;
		ctr0 <= '0';
		ctr1 <= '1';
		x <= "0000000000000000"; 
		y <= "0000000000000000"; 
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '1';
		x <= "0000000000000000"; 
		y <= "0000000000000000"; 
		wait for 0.1 ns;
		
		ctr0 <= '0';
		ctr1 <= '0';
		x <= "1000000000101101"; -- -32723  diff = -32745 = 1000000000010111 and sum = -32701 = 1000000001000011
		y <= "0000000000010110"; -- 22 
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '0';
		x <= "1000000000101101";
		y <= "0000000000010110";
		wait for 0.1 ns;
		ctr0 <= '0';
		ctr1 <= '1';
		x <= "1000000000101101";
		y <= "0000000000010110";
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '1';
		x <= "1000000000101101";
		y <= "0000000000010110";
		wait for 0.1 ns;

		ctr0 <= '0';
		ctr1 <= '0';
		x <= "1111111111111111"; -- -1  sum = -2 = 1111111111111110 and diff = 0 
		y <= "1111111111111111"; -- -1
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '0';
		x <= "1111111111111111"; 
		y <= "1111111111111111"; 
		wait for 0.1 ns;
		ctr0 <= '0';
		ctr1 <= '1';
		x <= "1111111111111111"; 
		y <= "1111111111111111"; 
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '1';
		x <= "1111111111111111"; 
		y <= "1111111111111111"; 
		wait for 0.1 ns;
		
		ctr0 <= '0';
		ctr1 <= '0';
		x <= "0000000001100011"; -- 99 sum = 197 = 0000000011000101 and diff = 1 = 0000000000000001
		y <= "0000000001100010"; -- 98
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '0';
		x <= "0000000001100011"; 
		y <= "0000000001100010"; 
		wait for 0.1 ns;
		ctr0 <= '0';
		ctr1 <= '1';
		x <= "0000000001100011"; 
		y <= "0000000001100010"; 
		wait for 0.1 ns;
		ctr0 <= '1';
		ctr1 <= '1';
		x <= "0000000001100011"; 
		y <= "0000000001100010"; 
		wait for 0.1 ns;
		
		ctr0 <= '1';
		ctr1 <= '0';
		x <= "0111111111111111"; 
		y <= "0111111111111111";
		wait for 0.1 ns;
		
		

		
		
end process;
end tb ;