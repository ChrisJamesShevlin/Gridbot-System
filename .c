

Skip to content
Using Gmail with screen readers
Conversations
11.53 GB of 15 GB (76%) used
Terms · Privacy · Program Policies
Last account activity: 13 hours ago
Details
//+------------------------------------------------------------------+
//|                                                      MyExpert.mq4|
//|                        Copyright 2021, MetaQuotes Software Corp. |
//|                                       http://www.metaquotes.net/ |
//+------------------------------------------------------------------+
#property strict

// Input parameters
input double TakeProfitPips = 10.0;
input double DistancePips = 5.0;
input double LotSize = 0.1; // Added input parameter for lot size
double firstBuyPrice = 0.0;
double firstSellPrice = 0.0;

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
   // Place initial Buy and Sell orders
   firstBuyPrice = NormalizeDouble(Ask, _Digits);
   firstSellPrice = NormalizeDouble(Bid, _Digits);
   
   // Use LotSize for the volume parameter in OrderSend
   int ticketBuy = OrderSend(Symbol(), OP_BUY, LotSize, Ask, 2, 0, firstBuyPrice + TakeProfitPips * Point, "First Buy", 0, 0, clrGreen);
   int ticketSell = OrderSend(Symbol(), OP_SELL, LotSize, Bid, 2, 0, firstSellPrice - TakeProfitPips * Point, "First Sell", 0, 0, clrRed);
   
   if(ticketBuy < 0 || ticketSell < 0)
     {
      Print("Error opening initial orders: ", GetLastError());
     }
   
   return(INIT_SUCCEEDED);
  }

//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
   
  }

//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
  {
   // Check for Buy condition
   if(Bid < firstBuyPrice - DistancePips * Point)
     {
      firstBuyPrice = NormalizeDouble(Bid, _Digits); // Update the price for the next order
      int ticket = OrderSend(Symbol(), OP_BUY, LotSize, Ask, 2, 0, firstBuyPrice + TakeProfitPips * Point, "Additional Buy", 0, 0, clrGreen);
      
      if(ticket < 0)
        {
         Print("Error opening additional Buy order: ", GetLastError());
        }
     }
   
   // Check for Sell condition
   if(Ask > firstSellPrice + DistancePips * Point)
     {
      firstSellPrice = NormalizeDouble(Ask, _Digits); // Update the price for the next order
      int ticket = OrderSend(Symbol(), OP_SELL, LotSize, Bid, 2, 0, firstSellPrice - TakeProfitPips * Point, "Additional Sell", 0, 0, clrRed);
      
      if(ticket < 0)
        {
         Print("Error opening additional Sell order: ", GetLastError());
        }
     }
  }
//+------------------------------------------------------------------+
GridBot_update.txt
Displaying GridBot_update.txt.
