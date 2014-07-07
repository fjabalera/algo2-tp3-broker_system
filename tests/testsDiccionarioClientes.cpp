// g++ -g testsDiccionarioClientes.cpp -o tdc
// valgrind --leak-check=full ./tdc

#include "../mini_test.h"
#include "../wolfie/DiccionarioClientes.h"
#include "../Tipos.h"

using namespace std;

void test_crear_diccionario_pocos_clientes() 
{
	DiccionarioClientes<aed2::Nat> dc(10);
	ASSERT_EQ(10, dc.capacidad());
}

void test_definir_un_cliente() 
{
	DiccionarioClientes<string> dc(10);
	string nombre = "Lolita";
	ASSERT_EQ(false, dc.Definido(31));
	dc.Definir(31, nombre);
	ASSERT_EQ(true, dc.Definido(31));
}

void test_definir_dos_clientes() 
{
	DiccionarioClientes<string> dc(10);
	string nombre = "Lolita";
	dc.Definir(31, nombre);
	dc.Definir(32, nombre);
	ASSERT_EQ(true, dc.Definido(31));
	ASSERT_EQ(true, dc.Definido(32));
	ASSERT_EQ(false, dc.Definido(33));
}

void test_definir_todos_los_clientes() 
{
	DiccionarioClientes<string> dc(5);
	string nombre = "Lolita";
	dc.Definir(31, nombre);
	dc.Definir(32, nombre);
	dc.Definir(67, nombre);
	dc.Definir(9, nombre);
	dc.Definir(125, nombre);
	ASSERT_EQ(true, dc.Definido(31));
	ASSERT_EQ(true, dc.Definido(32));
	ASSERT_EQ(false, dc.Definido(33));
	ASSERT_EQ(true, dc.Definido(125));
	ASSERT_EQ(false, dc.Definido(76));
	ASSERT_EQ(false, dc.Definido(90));
	ASSERT_EQ(true, dc.Definido(67));
}

void test_obtener_un_cliente()
{
	DiccionarioClientes<string> dc(5);
	string nombre = "Lolita";
	dc.Definir(31, nombre);
	ASSERT_EQ("Lolita", dc.Obtener(31));
}

void test_obtener_entre_varios_clientes()
{
	DiccionarioClientes<string> dc(5);
	string nombre1 = "Lolita1";
	string nombre2 = "Lolita2";
	string nombre3 = "Lolita3";
	string nombre4 = "Lolita4";
	string nombre5 = "Lolita5";
	dc.Definir(31, nombre1);
	dc.Definir(321, nombre2);
	dc.Definir(1, nombre3);
	dc.Definir(41, nombre4);
	dc.Definir(19, nombre5);
	ASSERT_EQ("Lolita1", dc.Obtener(31));
	ASSERT_EQ("Lolita2", dc.Obtener(321));
	ASSERT_EQ("Lolita3", dc.Obtener(1));
	ASSERT_EQ("Lolita4", dc.Obtener(41));
	ASSERT_EQ("Lolita5", dc.Obtener(19));
}


int main() 
{
	RUN_TEST(test_crear_diccionario_pocos_clientes);
	RUN_TEST(test_definir_un_cliente);
	RUN_TEST(test_definir_dos_clientes);
	RUN_TEST(test_definir_todos_los_clientes);
	RUN_TEST(test_obtener_un_cliente);
	RUN_TEST(test_obtener_entre_varios_clientes);
	
	return 0;
}
