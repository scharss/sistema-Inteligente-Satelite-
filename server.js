// server.js
import express from 'express';
import { Server as SocketIOServer } from 'socket.io';
import http from 'http';
import { SerialPort } from 'serialport';
import { ReadlineParser } from '@serialport/parser-readline';

const app = express();
const server = http.createServer(app);
const io = new SocketIOServer(server);

const portName = 'COM5'; // Reemplaza con el puerto correcto

const port = new SerialPort({ path: portName, baudRate: 9600 });

const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

app.use(express.static('public'));

parser.on('data', (data) => {
  console.log('Datos recibidos del Arduino: ', data.trim());
  io.emit('arduinoData', data.trim());  // Envía los datos a los clientes conectados
});

port.on('error', (err) => {
  console.error('Error en el puerto: ', err.message);
});

server.listen(3000, () => {
  console.log('Servidor escuchando en http://localhost:3000');
});
