//var log = require('./log.json');

module.exports = function (cardNo, callback) {

 var log = [{
 "card_number": 150,
 "signal strength": 70,
 "smart card status": "inserted",
 "quality": 100,
 "version": "3.5.2",
 "satellite": "INSAT-4A",
 "frequency": 11.001,
 "symbol rate": 27.5,
 "error": 102
}, {
 "card_number": 151,
 "signal strength": 70,
 "smart card status": "not inserted",
 "quality": 100,
 "version": "2.5.2",
 "satellite": "INSAT-4B",
 "frequency": 11.001,
 "symbol rate": 27.5,
 "error": 103
}, {
 "card_number": 152,
 "signal strength": 40,
 "smart card status": "insufficient balance",
 "quality": 100,
 "version": "3.5.2",
 "satellite": "INSAT-4C",
 "frequency": 11.001,
 "symbol rate": 27.5,
 "error": 104
}, {
 "card_number": 153,
 "signal strength": 70,
 "smart card status": "inserted",
 "quality": 20,
 "version": "3.5.2",
 "satellite": "INSAT-4A",
 "frequency": 11.001,
 "symbol rate": 27.5,
 "error": false
}, {
 "card_number": 155,
 "signal strength": 70,
 "smart card status": "inserted",
 "quality": 100,
 "version": "3.5.2",
 "satellite": "INSAT-4A",
 "frequency": 11.001,
 "symbol rate": 27.5,
 "error": 201
},{
 "card_number": 156,
 "signal strength": 70,
 "smart card status": "inserted",
 "quality": 100,
 "version": "3.5.2",
 "satellite": "INSAT-4A",
 "frequency": 11.001,
 "symbol rate": 27.5,
 "error": 401
},
];

 log.forEach(function(user){
    var reply='';
   if(user.card_number == cardNo) {
     reply="The signal strength is "+user["signal strength"]+ ", the signal quality is "+user["quality"]+ ", the frequency is "+user["frequency"]+" gigahertz and "+ " the symbol rate is "+user["symbol rate"];
     if (user['signal strength']<50)
     reply+=". I noticed that your signal strength is low. You could try switching to another satellite for better quality.";
     else if (user['signal quality']<50)
     reply+". I noticed that your signal quality is low. You could try checking the reciever for possible interferences to get better quality.";
     callback(reply);
   }


 });
};
