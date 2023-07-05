# Nota final: 9

# Documentación (5/5)
* Muy buen manual de usuario, muy descriptivo!
* Detallado manual técnico, explicando los puntos centrales del diseño de hilos y de la lógica de juego.


# UX/Jugabilidad (4.5/5)
* Les quedó muy bonita la interfaz de lobby, la única crítica que tengo es que puede pasar de que al crear partida te olvides de mirar el codigo de la sala, por lo que tengas que cerrar la ventana y volverla a abrir, estaría bueno que el codigo figure en la pantalla inicial una vez creada para recordarla y poder así pasarselás a los amigos con los cuales querés jugar.

* El sonido de algunos eventos se cortan un poco abruptamente, entiendo yo porque ocurre un cambio de estado del jugador/zombie que hace que ese sonido se detenga. Dejen que se reproduzca todo el sonido para que la experiencia sea mas amena.

* Al igual que con el sonido, algunas animaciones también sufren cortes abruptos, un ejemplo de esto son las granadas y el ataque aereo. Cuando suceden la animación o no se ve directamente, o se ven 1 o 2 frames nomás. Pareciera que la animación ocurre muy rápido y es imperceptible, podrían definir mediante archivo de configuración de que la animación se vea mas lenta (que figure el mismo frame por X mili segundos)

# Robustez / Valgrind (3/5)
* El server tiene varios conditional jumps over unitialized variables y memory leaks de hilos no liberados acordemente. dejo una traza de valgrind

```
==36065== Memcheck, a memory error detector
==36065== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==36065== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==36065== Command: l4dserver 2020
==36065== 
Nuevo jugador
==36065== Thread 4:
==36065== Conditional jump or move depends on uninitialised value(s)
==36065==    at 0x157130: Survival::update(float) (in /usr/local/bin/l4dserver)
==36065==    by 0x13995A: GameLogic::udpate_game() (in /usr/local/bin/l4dserver)
==36065==    by 0x12E46C: Game::run() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A165: Thread::main() (in /usr/local/bin/l4dserver)
==36065==    by 0x12AAFD: void std::__invoke_impl<void, void (Thread::*)(), Thread*>(std::__invoke_memfun_deref, void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12AA50: std::__invoke_result<void (Thread::*)(), Thread*>::type std::__invoke<void (Thread::*)(), Thread*>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A9B0: void std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A965: std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::operator()() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A945: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> > >::_M_run() (in /usr/local/bin/l4dserver)
==36065==    by 0x498A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==36065==    by 0x4C75B42: start_thread (pthread_create.c:442)
==36065==    by 0x4D06BB3: clone (clone.S:100)
==36065==  Uninitialised value was created by a heap allocation
==36065==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==36065==    by 0x12ABE2: MatchMananger::create_game(Queue<GameDTO, std::deque<GameDTO, std::allocator<GameDTO> > >*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int&, int&, GameMode&, signed char&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12CC3A: PlayerSender::init_player_receiver() (in /usr/local/bin/l4dserver)
==36065==    by 0x12C8D6: PlayerSender::run() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A165: Thread::main() (in /usr/local/bin/l4dserver)
==36065==    by 0x12AAFD: void std::__invoke_impl<void, void (Thread::*)(), Thread*>(std::__invoke_memfun_deref, void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12AA50: std::__invoke_result<void (Thread::*)(), Thread*>::type std::__invoke<void (Thread::*)(), Thread*>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A9B0: void std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A965: std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::operator()() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A945: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> > >::_M_run() (in /usr/local/bin/l4dserver)
==36065==    by 0x498A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==36065==    by 0x4C75B42: start_thread (pthread_create.c:442)
==36065== 
==36065== Conditional jump or move depends on uninitialised value(s)
==36065==    at 0x1571A6: Survival::update(float) (in /usr/local/bin/l4dserver)
==36065==    by 0x13995A: GameLogic::udpate_game() (in /usr/local/bin/l4dserver)
==36065==    by 0x12E46C: Game::run() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A165: Thread::main() (in /usr/local/bin/l4dserver)
==36065==    by 0x12AAFD: void std::__invoke_impl<void, void (Thread::*)(), Thread*>(std::__invoke_memfun_deref, void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12AA50: std::__invoke_result<void (Thread::*)(), Thread*>::type std::__invoke<void (Thread::*)(), Thread*>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A9B0: void std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A965: std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::operator()() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A945: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> > >::_M_run() (in /usr/local/bin/l4dserver)
==36065==    by 0x498A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==36065==    by 0x4C75B42: start_thread (pthread_create.c:442)
==36065==    by 0x4D06BB3: clone (clone.S:100)
==36065==  Uninitialised value was created by a heap allocation
==36065==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==36065==    by 0x12ABE2: MatchMananger::create_game(Queue<GameDTO, std::deque<GameDTO, std::allocator<GameDTO> > >*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int&, int&, GameMode&, signed char&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12CC3A: PlayerSender::init_player_receiver() (in /usr/local/bin/l4dserver)
==36065==    by 0x12C8D6: PlayerSender::run() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A165: Thread::main() (in /usr/local/bin/l4dserver)
==36065==    by 0x12AAFD: void std::__invoke_impl<void, void (Thread::*)(), Thread*>(std::__invoke_memfun_deref, void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12AA50: std::__invoke_result<void (Thread::*)(), Thread*>::type std::__invoke<void (Thread::*)(), Thread*>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A9B0: void std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A965: std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::operator()() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A945: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> > >::_M_run() (in /usr/local/bin/l4dserver)
==36065==    by 0x498A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==36065==    by 0x4C75B42: start_thread (pthread_create.c:442)
==36065== 
Se desconecto el cliente
Se cerro la cola correctamente
q
Unexpected exception: The queue is already closed.
==36065== 
==36065== FILE DESCRIPTORS: 3 open (3 std) at exit.
==36065== 
==36065== HEAP SUMMARY:
==36065==     in use at exit: 1,512 bytes in 5 blocks
==36065==   total heap usage: 4,053 allocs, 4,048 frees, 454,566 bytes allocated
==36065== 
==36065== Thread 1:
==36065== 64 bytes in 1 blocks are indirectly lost in loss record 1 of 5
==36065==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==36065==    by 0x12DB9B: __gnu_cxx::new_allocator<GameDTO*>::allocate(unsigned long, void const*) (in /usr/local/bin/l4dserver)
==36065==    by 0x12DAF1: std::allocator_traits<std::allocator<GameDTO*> >::allocate(std::allocator<GameDTO*>&, unsigned long) (in /usr/local/bin/l4dserver)
==36065==    by 0x12D903: std::_Deque_base<GameDTO, std::allocator<GameDTO> >::_M_allocate_map(unsigned long) (in /usr/local/bin/l4dserver)
==36065==    by 0x12D563: std::_Deque_base<GameDTO, std::allocator<GameDTO> >::_M_initialize_map(unsigned long) (in /usr/local/bin/l4dserver)
==36065==    by 0x12D361: std::_Deque_base<GameDTO, std::allocator<GameDTO> >::_Deque_base() (in /usr/local/bin/l4dserver)
==36065==    by 0x12D243: std::deque<GameDTO, std::allocator<GameDTO> >::deque() (in /usr/local/bin/l4dserver)
==36065==    by 0x12D2B6: std::queue<GameDTO, std::deque<GameDTO, std::allocator<GameDTO> > >::queue<std::deque<GameDTO, std::allocator<GameDTO> >, void>() (in /usr/local/bin/l4dserver)
==36065==    by 0x12D07E: Queue<GameDTO, std::deque<GameDTO, std::allocator<GameDTO> > >::Queue(unsigned int) (in /usr/local/bin/l4dserver)
==36065==    by 0x12C7BB: PlayerSender::PlayerSender(Socket*, std::atomic<bool>&, std::atomic<bool>&, MatchMananger*, int&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12DD11: Player::Player(Socket, MatchMananger*, int) (in /usr/local/bin/l4dserver)
==36065==    by 0x127DA3: Acceptor::run() (in /usr/local/bin/l4dserver)
==36065== 
==36065== 288 bytes in 1 blocks are possibly lost in loss record 2 of 5
==36065==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==36065==    by 0x40147D9: calloc (rtld-malloc.h:44)
==36065==    by 0x40147D9: allocate_dtv (dl-tls.c:375)
==36065==    by 0x40147D9: _dl_allocate_tls (dl-tls.c:634)
==36065==    by 0x4C76834: allocate_stack (allocatestack.c:430)
==36065==    by 0x4C76834: pthread_create@@GLIBC_2.34 (pthread_create.c:647)
==36065==    by 0x498A388: std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >, void (*)()) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==36065==    by 0x12A34F: std::thread::thread<void (Thread::*)(), Thread*, void>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A0E2: Thread::start() (in /usr/local/bin/l4dserver)
==36065==    by 0x12DD43: Player::Player(Socket, MatchMananger*, int) (in /usr/local/bin/l4dserver)
==36065==    by 0x127DA3: Acceptor::run() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A165: Thread::main() (in /usr/local/bin/l4dserver)
==36065==    by 0x12AAFD: void std::__invoke_impl<void, void (Thread::*)(), Thread*>(std::__invoke_memfun_deref, void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12AA50: std::__invoke_result<void (Thread::*)(), Thread*>::type std::__invoke<void (Thread::*)(), Thread*>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A9B0: void std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /usr/local/bin/l4dserver)
==36065== 
==36065== 288 bytes in 1 blocks are possibly lost in loss record 3 of 5
==36065==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==36065==    by 0x40147D9: calloc (rtld-malloc.h:44)
==36065==    by 0x40147D9: allocate_dtv (dl-tls.c:375)
==36065==    by 0x40147D9: _dl_allocate_tls (dl-tls.c:634)
==36065==    by 0x4C76834: allocate_stack (allocatestack.c:430)
==36065==    by 0x4C76834: pthread_create@@GLIBC_2.34 (pthread_create.c:647)
==36065==    by 0x498A388: std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >, void (*)()) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==36065==    by 0x12A34F: std::thread::thread<void (Thread::*)(), Thread*, void>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A0E2: Thread::start() (in /usr/local/bin/l4dserver)
==36065==    by 0x12CE54: PlayerSender::init_player_receiver() (in /usr/local/bin/l4dserver)
==36065==    by 0x12C8D6: PlayerSender::run() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A165: Thread::main() (in /usr/local/bin/l4dserver)
==36065==    by 0x12AAFD: void std::__invoke_impl<void, void (Thread::*)(), Thread*>(std::__invoke_memfun_deref, void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12AA50: std::__invoke_result<void (Thread::*)(), Thread*>::type std::__invoke<void (Thread::*)(), Thread*>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A9B0: void std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /usr/local/bin/l4dserver)
==36065== 
==36065== 480 bytes in 1 blocks are indirectly lost in loss record 4 of 5
==36065==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==36065==    by 0x12DC51: __gnu_cxx::new_allocator<GameDTO>::allocate(unsigned long, void const*) (in /usr/local/bin/l4dserver)
==36065==    by 0x12DBCA: std::allocator_traits<std::allocator<GameDTO> >::allocate(std::allocator<GameDTO>&, unsigned long) (in /usr/local/bin/l4dserver)
==36065==    by 0x12DB1F: std::_Deque_base<GameDTO, std::allocator<GameDTO> >::_M_allocate_node() (in /usr/local/bin/l4dserver)
==36065==    by 0x12D980: std::_Deque_base<GameDTO, std::allocator<GameDTO> >::_M_create_nodes(GameDTO**, GameDTO**) (in /usr/local/bin/l4dserver)
==36065==    by 0x12D5B9: std::_Deque_base<GameDTO, std::allocator<GameDTO> >::_M_initialize_map(unsigned long) (in /usr/local/bin/l4dserver)
==36065==    by 0x12D361: std::_Deque_base<GameDTO, std::allocator<GameDTO> >::_Deque_base() (in /usr/local/bin/l4dserver)
==36065==    by 0x12D243: std::deque<GameDTO, std::allocator<GameDTO> >::deque() (in /usr/local/bin/l4dserver)
==36065==    by 0x12D2B6: std::queue<GameDTO, std::deque<GameDTO, std::allocator<GameDTO> > >::queue<std::deque<GameDTO, std::allocator<GameDTO> >, void>() (in /usr/local/bin/l4dserver)
==36065==    by 0x12D07E: Queue<GameDTO, std::deque<GameDTO, std::allocator<GameDTO> > >::Queue(unsigned int) (in /usr/local/bin/l4dserver)
==36065==    by 0x12C7BB: PlayerSender::PlayerSender(Socket*, std::atomic<bool>&, std::atomic<bool>&, MatchMananger*, int&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12DD11: Player::Player(Socket, MatchMananger*, int) (in /usr/local/bin/l4dserver)
==36065== 
==36065== 936 (392 direct, 544 indirect) bytes in 1 blocks are definitely lost in loss record 5 of 5
==36065==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==36065==    by 0x127D87: Acceptor::run() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A165: Thread::main() (in /usr/local/bin/l4dserver)
==36065==    by 0x12AAFD: void std::__invoke_impl<void, void (Thread::*)(), Thread*>(std::__invoke_memfun_deref, void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12AA50: std::__invoke_result<void (Thread::*)(), Thread*>::type std::__invoke<void (Thread::*)(), Thread*>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A9B0: void std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /usr/local/bin/l4dserver)
==36065==    by 0x12A965: std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::operator()() (in /usr/local/bin/l4dserver)
==36065==    by 0x12A945: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> > >::_M_run() (in /usr/local/bin/l4dserver)
==36065==    by 0x498A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==36065==    by 0x4C75B42: start_thread (pthread_create.c:442)
==36065==    by 0x4D06BB3: clone (clone.S:100)
==36065== 
==36065== LEAK SUMMARY:
==36065==    definitely lost: 392 bytes in 1 blocks
==36065==    indirectly lost: 544 bytes in 2 blocks
==36065==      possibly lost: 576 bytes in 2 blocks
==36065==    still reachable: 0 bytes in 0 blocks
==36065==         suppressed: 0 bytes in 0 blocks
==36065== 
==36065== For lists of detected and suppressed errors, rerun with: -s
==36065== ERROR SUMMARY: 5 errors from 5 contexts (suppressed: 0 from 0)

```

* Hay atributos del DTO no inicializados que reporta valgrind

```
==36744== Thread 3:
==36744== Conditional jump or move depends on uninitialised value(s)
==36744==    at 0x1212C9: ClientDeserializer::deserialize_game_dto(bool*) (in /usr/local/bin/l4dclient)
==36744==    by 0x124B60: ClientReceiver::run() (in /usr/local/bin/l4dclient)
==36744==    by 0x126EFF: Thread::main() (in /usr/local/bin/l4dclient)
==36744==    by 0x129721: void std::__invoke_impl<void, void (Thread::*)(), Thread*>(std::__invoke_memfun_deref, void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dclient)
==36744==    by 0x129674: std::__invoke_result<void (Thread::*)(), Thread*>::type std::__invoke<void (Thread::*)(), Thread*>(void (Thread::*&&)(), Thread*&&) (in /usr/local/bin/l4dclient)
==36744==    by 0x1295D4: void std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /usr/local/bin/l4dclient)
==36744==    by 0x129589: std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> >::operator()() (in /usr/local/bin/l4dclient)
==36744==    by 0x129569: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (Thread::*)(), Thread*> > >::_M_run() (in /usr/local/bin/l4dclient)
==36744==    by 0x60022B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==36744==    by 0x62EBB42: start_thread (pthread_create.c:442)
==36744==    by 0x637CBB3: clone (clone.S:100)
==36744==  Uninitialised value was created by a stack allocation
==36744==    at 0x120D1A: ClientDeserializer::deserialize_game_dto(bool*) (in /usr/local/bin/l4dclient)
```


* Hay ocasiones que el cliente termina en un segmentation fault debido a un invalid read al intentar renderizar las fuentes de gameover, puede que tenga relación con las variables no inicializadas mencionadas previamente.



# Performance (5/5)
Buen trabajo en la performance!!

# Instalación (4.5/5)
- Hay un error en el CMAKE, donde hacen un `INSTALL EQUAL ON` que no funciona cuando quieren instalar el juego. Deberían
hacer directamente `if(INSTALL)` (si la variable está en ON se toma como True en Cmake, mientras que de otra forma es False) 
y no usar el operador EQUAL (el operador `EQUAL` espera recibir o un string o una variable, no se si CMake está interpretando al argumento  `ON` como un string o como una variable (que vale "null" porque no fue definida hasta este momento) mientras que la opción `INSTALL` es una variable booleana). Una vez corregido ese problema el juego se instala sin problemas en los paths adecuados.

# Features (5/5)
## Zombies
### Infectados
- [x] Caminan o permanecen quietos si no son molestados
- [x] Cuando el jugador esté en el rango de vision los persigue 
- [x] golpe con mordidas o golpes

### Jumper
- [ ] Salta sobre sus victimas
- [x] produce daño cuando cae sobre las victimas
- [ ] salto tiene animación previa de aviso

### Witch
- [x] ocasionalmente grita para atraer infectados

### Spear
- [x] usan armas como lanzas

### Venom
- [x] ataque a distancia
- [x] daña a todo jugador que esté en contacto con el ataque

## Jugador
- [x] Munición infinita
- [x] Tiempo de recarga 
- [x] Todos salvo P90 pueden lanzar granadas explosivas y de humo


### IDF
- [x] rafaga de 20 balas 
- [x] daño a corta distancia alto
- [x] daño menor a larga distancia
- [x] Recarga cada 50 rafagas

### P90

- [x] rafagas de 10 balas
- [x] daño no reducido a largas distancias
- [x] recarga cada 30 rafagas

### Scout
- [x] Rifle de 1 bala
- [x] Atraviesa infectados
- [x] Daño se reduce por cada impacto entre infectados
- [x] recarga cada 20 bbalas


## Granadas
- [x] Son infinitas
- [x] hay un tiempo de espera entre lanzamientos
- [x] explosiva: daña enemigos en la zona. Daña a jugadores aliados también
- [x] humo: no producen daño. Los infectados quedan aturdidos y dejan de correr y saltar, siguen caminando

## Bombardeo aereo
- [x] Solo P90 puede invocarlo
- [x] caen granadas por todo el escenario salvo la zona cercana al jugador
- [x] tiempo de espera entre bombardeos mayor

## Vida
- [x] Los jugadores tienen vida.
- [x] Los zombies tienen vida.
- [x] Cuando llega a cero son derribados
- [x] Los jugadores derribados pueden recibir asistencia por otro jugador y seguir jugando
- [x] el jugador recuperado se levanta con mitad de vida
- [x] a los 3 derribos muere inmediatamente.
- [x] Si jugador derribado no es asistido, muere

## Ataque y colisiones
- [x] soldados y zombies pueden colisionar
- [x] hay un hitbox para detectar zombies en el eje y


## Escenario
- [x] los crateres son zona por la que no podés caminar
- [x] hay una camara que sigue al jugador
- [x] Te podés mover a los costados
- [x] Hay una ilusion de paralaje

## Modos de juego
### Clear the zone
- [x] cantidad fija de zombies. Jugador gana cuando elimina a todos

### Survival
- [x] Cantidad infinita de zombies.
- [x] cada vez se hacen mas fuertes, resistentes y veloces
- [x] termina cuando jugadores mueren

## Fin de partida
- [x] se muestra estadisticas de juego (cantidad de eliminados, balas disparadas, tiempo de partida)
- [ ] En modo survival las estadisticas se guardan y se muestra un ranking historico (1 ranking por cada estadistica) que se muestra al final del modo

## Interfaz gráfica
- [x] Se muestra la vida de cada soldado
- [x] Se muestra las rafagas restantes antes de recargar
- [x] Se muestra tiempo restante para lanzar granada
- [x] Se muestra balas disparadas
- [x] Se muestra infectados eliminados
- [x] Se muestra tiempo transcurrido
## Controles
- [x] se controla via teclado
- [x] Recarga automatica (cuando te quedás sin balas)
- [x] Recarga manual (mediante botón de recarga)
- [x] distancia de lanzado de granada depende de cuanto tiempo se mantiene presionado la tecla
- [x] Si mantenés mucho tiempo presionado la tecla de lanzar granada, explota en la mano
	* Si bien vi que el código está y la configuración tmb, funciona raro el caso de prueba este. Bajé el tiempo para que
	explote en la mano a 5 segundos y dejé presionado mucho tiempo, pero la granada nunca explotaba, sino que al soltar la bomba me explota al lado

## sonidos
- [x] cuando hay disparo
- [x] cuando hay expĺosion
	* hay algunos sonidos que se cortan muy rapido por algún cambio de estado del jugador, habria que revisar
	para que termine el sonido en su totalidad.

## Musica
- [x] Buen groove de la musica
## Animaciones
- [x] Muy buenas animaciones!!

## Configuraciones
- [x] Hay configuraciones, aunque debo criticar una, que es el game factory. El uso de `std::rand`
      no te da una distribución uniforme como quisieran haber hecho ustedes, causando de que si modificás
      el archivo para que tengan 1% de probablidad para que aparezcan cualquiera de los zombies salvo uno
      que va a tener 96%, en la realidad ese zombie nunca se vea.

      En la documentación de rand dice que el uso de la operación modulo genera un [bias en el resultado](https://en.cppreference.com/w/cpp/numeric/random/rand) y que se recomienda hacer una división para tener algo mas
      uniforme. Sino podrían haber usado un `std::uniform_in_distribution`
## Cheat
- [ ] No hay cheats

## Tests
- [x] Muy buena cobertura de tests!!

# Cliente - Servidor (5/5)

# Código (5/5)
## Cliente
* En vez de tener un hilo para lobby sender y lobby receiver y luego otros dos hilos para enviar y recibir en el juego, podrías haber tenido 2 hilos y que envien y reciban en función de un booleano atomico que diga en qué estado está. 


## Server
* El hilo main del server tiene un bloque try catch especifico para `runtime_error` en vez de algo más genérico como
`std::exception`. Si el día de mañana agregás llamados a funciones que puedan lanzar (el uso de `new`, algo con
vectores, lo que sea) el server va a terminar con un segmentation fault. Atajate de cualquier caso de falla haciendo
tu código robusto ante fallas catcheando todo tipo de excepciones (y agregá un catch de elipsis para excepciones
de biblioteca de terceros que no hereden de `std:.exception`)
