// This code tests the Pool class

#include "packet.hpp"
#include "pool.hpp"
#include <random>
#include <string>
#include <iostream>

int main()
{

  {
    std::cout << "\nInfo: Create pool\n";
    Pool<Packet<5>, 3> pool1{};
    pool1.status( "pool1" );

    // simple allocation
    std::cout << "\nInfo: allocate first packet\n";
    auto pkt1 = pool1.alloc();
    assert( pkt1 != nullptr );
    std::cout << "pkt1=" << pkt1->to_string() << '\n';
    pool1.status( "pool1" );

    std::cout << "\nInfo: allocate second packet using move semantics\n";
    auto pkt2 = pool1.alloc( Packet<5>{ 1, 2, { 'H', 'e', 'l', 'l', 'o' }} );
    assert( pkt2 != nullptr );
    std::cout << "pkt2=" << pkt2->to_string() << '\n';
    pool1.status( "pool1" );

    std::cout << "\nInfo: allocate third packet\n";
    std::memcpy( &pkt2->data[0], "World", 5 );
    auto pkt3 = pool1.alloc(*pkt2);
    std::cout << "pkt3=" << pkt3->to_string() << '\n';
    pool1.status( "pool1" );

    std::cout << "\nInfo: attempt fourth packet\n";
    auto pkt4 = pool1.alloc();
    assert( pkt4 == nullptr );

    std::cout << "\nInfo: free second packet\n";
    pool1.free( pkt2 );
    pool1.status( "pool1" );

    std::cout << "\nInfo: attempt to free a second time second packet\n";
    pool1.free( pkt2 );
    pool1.status( "pool1" );

    std::cout << "\nInfo: attempt to free a nullptr\n";
    pool1.free( nullptr );
    pool1.status( "pool1" );

    std::cout << "Destroying pool\n";
  }

  std::cout << "Finished testing\n";
  return 0;
}
