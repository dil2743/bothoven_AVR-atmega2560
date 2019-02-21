# bothoven_AVR-atmega2560

The map as shown in fig. tack.jpg of the arena and musical notes are saved in the bot and by using ultrasonic, rotatory encoder and IR-sensor it is traversing the graph.
The note which is to be played is extracted by python file in laptop and is communicated by Zigbee to the bot.
According to the music file, the bot calculates the shortest path and try to reach it but if it found any blockage it is path it recalculates its shortest path by eliminating the block path.
So when the bot reaches a node containing appropriate music note it lowers down its arm to play the node.
