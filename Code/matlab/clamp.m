function z = clamp(x,y)
  z = max(min(round(x-2), y),1):max(min(round(x+2), y),1);