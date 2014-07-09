#include "Wolfie.h"

using namespace aed2;

Wolfie::Wolfie(){}

Wolfie::~Wolfie()
{
	// std::cout << "Called: ~Wolfie" << std::endl;
	delete _clientes;
	delete _titulos;
}

Wolfie::Wolfie(const Conj<Cliente>& clientes)
{
	_cantidadDeClientes = clientes.Cardinal();
	_clientes = new DiccionarioClientes<infoCliente>(_cantidadDeClientes);	
	Conj<Cliente>::const_Iterador itClientes = clientes.CrearIt();
	while (itClientes.HaySiguiente()) {
		_clientes->Definir(itClientes.Siguiente(), infoCliente());
		itClientes.Avanzar();
	}

	_titulos = new DiccionarioTitulos<infoTitulo>();
}

Nat Wolfie::CantidadDeClientes() const
{
	return _cantidadDeClientes;
}

Cliente Wolfie::IesimoCliente(Nat i) const
{
	return _clientes->Iesimo(i);
}

void Wolfie::AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones)
{
	infoTitulo titulo(max_acciones, cotizacion);
	_titulos->definir(nombre, titulo);
}

Nat Wolfie::CantidadDeTitulos() const
{
	int cantidadDeTitulos = 0;
	DiccionarioTitulos<infoTitulo>::const_Iterador itTitulos = _titulos->CrearIt();

	while(itTitulos.HaySiguiente()) {
		cantidadDeTitulos++;
		itTitulos.Avanzar();
	}

	return cantidadDeTitulos;
}

// PRE: 0 <= i < CantidadDeTitulos()
NombreTitulo Wolfie::IesimoTitulo(Nat i) const
{
	int iesimo = 1;
	String nombreIesimo;
	DiccionarioTitulos<infoTitulo>::const_Iterador itTitulos = _titulos->CrearIt();

	while(itTitulos.HaySiguiente()) {
		if (iesimo == i) return itTitulos.SiguienteClave();
		iesimo++;
		itTitulos.Avanzar();
	}
}

Nat Wolfie::MaxAccionesDe(const NombreTitulo& nombre_titulo) const
{
	return _titulos->obtener(nombre_titulo).cantidadMaximaDeAcciones;
}

Dinero Wolfie::CotizacionDe(const NombreTitulo& nombre_titulo) const
{
	return _titulos->obtener(nombre_titulo).cotizacion;	
}

bool Wolfie::EnAlza(const NombreTitulo& nombre_titulo) const
{
	return _titulos->obtener(nombre_titulo).enAlza;		
}

// PRE: no PrometeComprar(cliente)
void Wolfie::AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	infoCliente infoClienteActual(_clientes->Obtener(cliente));	

	if (infoClienteActual.titulos.definido(titulo)) {
		infoTituloCliente infoTituloClienteActual(infoClienteActual.titulos.obtener(titulo));
		infoTituloClienteActual.promesas.compra = promesa(true, limite, cantidad);
		
		infoClienteActual.titulos.definir(titulo, infoTituloClienteActual);
		_clientes->Definir(cliente, infoClienteActual);
	} else {
		infoTituloCliente infoTituloClienteActual;
		infoTituloClienteActual.promesas.compra = promesa(true, limite, cantidad);
		
		infoClienteActual.titulos.definir(titulo, infoTituloClienteActual);
		_clientes->Definir(cliente, infoClienteActual);
	}
}

bool Wolfie::PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);
	
	if (!infoClienteActual.titulos.definido(titulo)) return false;
	
	infoTituloCliente infoTituloClienteActual = infoClienteActual.titulos.obtener(titulo);

	return infoTituloClienteActual.promesas.compra.pendiente;
}

// PRE: no PrometeVender(cliente) y cantidad < AccionesPorCliente(cliente, titulo)
void Wolfie::AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	infoCliente infoClienteActual(_clientes->Obtener(cliente));	

	if (infoClienteActual.titulos.definido(titulo)) {
		infoTituloCliente infoTituloClienteActual(infoClienteActual.titulos.obtener(titulo));
		infoTituloClienteActual.promesas.venta = promesa(true, limite, cantidad);
		
		infoClienteActual.titulos.definir(titulo, infoTituloClienteActual);
		_clientes->Definir(cliente, infoClienteActual);
	} else {
		infoTituloCliente infoTituloClienteActual;
		infoTituloClienteActual.promesas.venta = promesa(true, limite, cantidad);
		
		infoClienteActual.titulos.definir(titulo, infoTituloClienteActual);
		_clientes->Definir(cliente, infoClienteActual);
	}	
}

bool Wolfie::PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);
	
	if (!infoClienteActual.titulos.definido(titulo)) return false;
	
	infoTituloCliente infoTituloClienteActual = infoClienteActual.titulos.obtener(titulo);

	return infoTituloClienteActual.promesas.venta.pendiente;
}

