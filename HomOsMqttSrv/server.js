var mosca = require('mosca')
/*
var ascoltatore = {
  //using ascoltatore
  type: 'mongo',
  url: 'mongodb://localhost:27017/mqtt',
  pubsubCollection: 'ascoltatori',
  mongo: {}
};
*/
var moscaSettings = {
  port: 8883,
  //  backend: ascoltatore,
  //  persistence: {
  //    factory: mosca.persistence.Mongo,
  //    url: 'mongodb://localhost:27017/mqtt'
  //  }
};

var server = new mosca.Server(moscaSettings);
server.on('ready', setup);

server.on('clientConnected', function (client) {
  console.log('client connected', client.id);
});

// Sending data from mosca to clients
var message = {
  topic: '/hello/world',
  payload: 'abcde', // or a Buffer
  qos: 0, // 0, 1, or 2
  retain: false // or true
};
server.publish(message, function () {
  console.log('done!');
});

// fired when a message is received
server.on('published', function (packet, client) {
  //console.log("published packet : ", packet, "\n");
  //console.log("published client : ", client, "\n");
  console.log("Message received from package : ", packet.payload.toString("utf-8"));
  // console.log(packet)

});

// fired when the mqtt server is ready
function setup() {
  console.log('Mosca server is up and running')
  console.log(moscaSettings.port);
  // server.authenticate = authenticate;
  //server.authorizePublish = authorizePublish;
  //server.authorizeSubscribe = authorizeSubscribe;
}

// Accepts the connection if the username and password are valid
server.authenticate = function (client, username, password, callback) {
  // To authenticate
  authorized = (username == "" && password.toString() == "");
  if (authorized) client.user = bir["kull"];
  callback(null, true);
  // To reject
  //callback(null, false);
}
// In this case the client authorized as alice can publish to /users/alice taking
// the username from the topic and verifing it is the same of the authorized user
server.authorizePublish = function (client, topic, payload, callback) {
  // To authenticate
  callback(null, true);
  // To reject
  //callback(null, false);
}

// In this case the client authorized as alice can subscribe to /users/alice taking
// the username from the topic and verifing it is the same of the authorized user
var authorizeSubscribe = function (client, topic, callback) {
  callback(null, client.user == topic.split('/')[1]);
  console.log(client.user);
}