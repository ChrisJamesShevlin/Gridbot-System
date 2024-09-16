# MyExpert Grid Trading Bot for MetaTrader 4 (MT4)

This repository contains the source code for **MyExpert**, a grid trading bot developed for **MetaTrader 4 (MT4)**. The bot uses a grid strategy to place buy and sell orders based on distance from the initial trade. The primary goal is to take advantage of market fluctuations by placing new orders at set intervals and taking profits based on predefined pip values.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Input Parameters](#input-parameters)
- [Trading Logic](#trading-logic)
- [Error Handling](#error-handling)
- [Customization](#customization)
- [License](#license)

## Overview

This bot opens an initial buy and sell order simultaneously, then continues placing additional orders at a specific pip distance from the initial order. The bot manages both long (buy) and short (sell) trades based on simple price action rules and predefined parameters, such as lot size, take profit, and distance between trades.

## Features

- **Grid Trading Strategy**: Opens buy and sell orders at a fixed pip distance from the initial orders.
- **Lot Size Control**: Configurable lot size for orders.
- **Take Profit**: Automatically closes trades when the price reaches a certain number of pips in profit.
- **Order Management**: Automatically updates the next order price as trades are executed.
- **Error Handling**: Prints detailed error messages for failed trades.

## Installation

1. **Download the Script**:
   Download the `MyExpert.mq4` file from this repository.

2. **Install on MetaTrader 4**:
   - Open MT4 and go to `File > Open Data Folder`.
   - Navigate to `MQL4 > Experts`.
   - Copy the downloaded `.mq4` file into the `Experts` folder.
   - Restart MT4 or refresh the `Expert Advisors` section in the Navigator.

3. **Apply the Expert Advisor**:
   - Open a chart for the currency pair you want to trade.
   - In the Navigator, under `Expert Advisors`, drag and drop the `MyExpert` EA onto the chart.
   - Configure input parameters as needed (see below).

## Input Parameters

You can customize the behavior of the bot using the following input parameters:

| Parameter        | Description                                        | Default Value |
|------------------|----------------------------------------------------|---------------|
| `TakeProfitPips` | The number of pips for take profit on each trade.   | 10.0          |
| `DistancePips`   | The pip distance between subsequent buy/sell orders| 5.0           |
| `LotSize`        | The lot size for each order placed by the bot.      | 0.1           |

These parameters allow you to fine-tune the bot's trading strategy based on your risk tolerance and market conditions.

## Trading Logic

1. **Initial Orders**:  
   When the EA is first initialized, it places a buy and a sell order at the current ask and bid prices, respectively. The initial buy and sell orders are only placed once unless the EA is restarted.

2. **Subsequent Orders**:  
   - If the market moves **down** by the specified distance (`DistancePips`) from the initial buy order, the bot places a new buy order at the updated price.
   - If the market moves **up** by the specified distance (`DistancePips`) from the initial sell order, the bot places a new sell order at the updated price.
   
3. **Take Profit**:  
   Each order has a take profit level set at `TakeProfitPips` from the entry price. Once the market reaches this level, the trade is closed.

### Example Workflow:
- Initial buy and sell orders are placed at the market prices.
- If the market price moves **5 pips** below the initial buy price, the bot places an additional buy order.
- If the market price moves **5 pips** above the initial sell price, the bot places an additional sell order.
- Each order will close automatically when it reaches **10 pips** of profit.

## Error Handling

The bot includes basic error handling to manage unsuccessful trades:

- If the order fails, the bot will print the error message using:
   ```mql4
   Print("Error opening initial orders: ", GetLastError());
   ```

This ensures that any issues with order placement are logged for troubleshooting.

## Customization

1. **Lot Size Adjustment**:
   You can adjust the lot size in the input parameters or directly in the code:
   ```mql4
   input double LotSize = 0.1;
   ```

2. **Pip Distance & Take Profit**:
   Modify the pip distance and take profit values by adjusting the `DistancePips` and `TakeProfitPips` parameters:
   ```mql4
   input double TakeProfitPips = 10.0;
   input double DistancePips = 5.0;
   ```

3. **Restarting and Resetting Orders**:
   By default, the bot ensures that the initial orders are only placed once, but you can reset this behavior by setting the `initialOrdersPlaced` flag to `false` under certain conditions, such as after a restart.

   ```mql4
   initialOrdersPlaced = false;
   ```

## License

This project is licensed under the MetaQuotes License for MT4. See the [LICENSE](./LICENSE) file for more details.

---

This Expert Advisor is designed to help you implement a grid trading strategy in MT4. It is intended as a starting point, and you can modify the code to suit your specific trading strategy or risk management preferences.
