public class Hello {
	private	int teste_int = 3;
	private double teste_double = 2.3;
		
		public Hello() {
		
		}
		
		public int get_int() {
			return this.teste_int;
		}
		
		public double get_double() {
			return this.teste_double;
		}
		
		public void set_int(int teste_int) {
			this.teste_int = teste_int;
		}
		
		public void set_double(double teste_double) {
			this.teste_double = teste_double;
		}
		
		public void hello() {
			System.out.println("Hello!");
		}
}