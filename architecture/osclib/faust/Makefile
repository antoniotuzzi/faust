subprojects := include src src/lib src/msg src/nodes src/osc src/threads
sources = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) 
objects = $(sources:.cpp=.o)

VPATH = $(subprojects)

CXXFLAGS ?= -O3 -Wall -Wuninitialized 
CXXFLAGS += -Wno-parentheses -I../oscpack -I../oscpack/osc $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"'

all : libOSCFaust.a

libOSCFaust.a : $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@
	
	
depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
clean :
	rm -f $(objects)
	rm -f libOSCFaust.a
	


# DO NOT DELETE

src/OSCControler.o: include/OSCControler.h src/nodes/FaustFactory.h src/msg/MessageDriven.h src/msg/MessageProcessor.h
src/OSCControler.o: src/lib/smartpointer.h src/osc/OSCSetup.h src/osc/OSCStream.h
src/OSCControler.o: ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h
src/OSCControler.o: ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h
src/OSCControler.o: src/lib/OSCFError.h src/nodes/RootNode.h include/OSCIO.h
src/lib/OSCFError.o: src/lib/OSCFError.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h
src/lib/OSCFError.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h
src/lib/OSCFError.o: ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h src/msg/Message.h
src/lib/OSCFError.o: src/lib/smartpointer.h
src/lib/OSCRegexp.o: src/lib/OSCRegexp.h src/lib/deelx.h
src/msg/Message.o: src/msg/Message.h src/lib/smartpointer.h src/lib/OSCFError.h src/osc/OSCStream.h
src/msg/Message.o: ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h
src/msg/Message.o: ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h
src/msg/MessageDriven.o: src/msg/Message.h src/lib/smartpointer.h src/msg/MessageDriven.h src/msg/MessageProcessor.h
src/msg/MessageDriven.o: src/osc/OSCAddress.h src/lib/OSCFError.h src/osc/OSCStream.h
src/msg/MessageDriven.o: ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/msg/MessageDriven.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/msg/MessageDriven.o: ../oscpack/ip/IpEndpointName.h src/lib/OSCRegexp.h src/lib/deelx.h
src/nodes/FaustFactory.o: src/nodes/FaustFactory.h src/msg/MessageDriven.h src/msg/MessageProcessor.h
src/nodes/FaustFactory.o: src/lib/smartpointer.h src/nodes/FaustNode.h src/nodes/RootNode.h
src/nodes/FaustNode.o: src/nodes/FaustNode.h src/msg/MessageDriven.h src/msg/MessageProcessor.h src/lib/smartpointer.h
src/nodes/FaustNode.o: src/msg/Message.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h
src/nodes/FaustNode.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h
src/nodes/FaustNode.o: ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h
src/nodes/RootNode.o: src/nodes/RootNode.h src/msg/MessageDriven.h src/msg/MessageProcessor.h src/lib/smartpointer.h
src/nodes/RootNode.o: src/msg/Message.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h
src/nodes/RootNode.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h
src/nodes/RootNode.o: ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h include/OSCControler.h
src/nodes/RootNode.o: include/OSCIO.h ../oscpack/ip/NetworkingUtils.h
src/osc/OSCAddress.o: src/osc/OSCAddress.h
src/osc/OSCIO.o: include/OSCIO.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/osc/OSCIO.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/osc/OSCIO.o: ../oscpack/ip/IpEndpointName.h
src/osc/OSCListener.o: src/osc/OSCListener.h src/lib/smartpointer.h src/msg/MessageProcessor.h
src/osc/OSCListener.o: ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h
src/osc/OSCListener.o: ../oscpack/osc/OscPacketListener.h ../oscpack/osc/OscReceivedElements.h
src/osc/OSCListener.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/PacketListener.h
src/osc/OSCListener.o: src/msg/Message.h ../oscpack/osc/OscReceivedElements.h ../oscpack/ip/IpEndpointName.h
src/osc/OSCSetup.o: src/osc/OSCSetup.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h
src/osc/OSCSetup.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h
src/osc/OSCSetup.o: ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h src/threads/TThreads.h
src/osc/OSCSetup.o: src/osc/OSCListener.h src/lib/smartpointer.h src/msg/MessageProcessor.h
src/osc/OSCSetup.o: ../oscpack/osc/OscPacketListener.h ../oscpack/osc/OscReceivedElements.h
src/osc/OSCSetup.o: ../oscpack/ip/PacketListener.h
src/osc/OSCStream.o: src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/osc/OSCStream.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/osc/OSCStream.o: ../oscpack/ip/IpEndpointName.h
src/threads/pthreads_impl.o: src/threads/TThreads.h