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
 "signal strength": 70,
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
 "quality": 100,
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
 "error": 105
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
   if(user.card_number == cardNo) {
     switch(user.error){
       case 102:
         callback("It seems like you have a hard drive failure. Please contact customer care at 1800-576-4321.");
         break;
       case 103:
         callback("Your firmware is out of date. Please open the menu using your remote and then select settings option. Then select the update firmware option.");
         break;
       case 104:
         callback("You have insufficient balance. Please recharge your viewing card.");
         break;
       case 105:
         callback("You have a viewing card error. Please keep the set top box on as I try to perform a reset.");
         //server_call_to_reset(vc_number)
         break;
      case 401:
         callback("Don't worry. Switch off the DishTV set top box directly from the main power switch. Next, take the VC card out of the set top box carefully. Re-insert the VC card with the chip going in first, facing downwards. ");
         break;
       case false:
         callback("Your set top box is fine. Check if your television is properly connected");
         break;



     }
   }
   else if(cardNo == 154){
     callback("The signal loss could be because of bad weather. (Cloudy sky, rainfall, gusty winds). Please contact a technician if the problem persists.");
   }
 });
};
