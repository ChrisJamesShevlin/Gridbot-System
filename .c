
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
bool initialOrdersPlaced = false; // Flag to ensure initial orders are placed only once

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
   // Check if initial orders have not been placed yet
   if(!initialOrdersPlaced)
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
      else
        {
         // Only if both orders are successfully opened, prevent them from being placed again
         initialOrdersPlaced = true;
        }
     }
   
   return(INIT_SUCCEEDED);
  }

//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
   // You can reset the flag here if you want the process to be repeatable after a restart or under certain conditions
   // initialOrdersPlaced = false;
  }

//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
  {
   // Subsequent orders logic remains unchanged, as it's not directly affected by the initial order placement control
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
GridBot_update2.0.txt
Displaying GridBot_update2.0.txt.
