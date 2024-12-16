PIDS=$(lsof -t -i:33333)
if [ -n "$PIDS" ]; then
  kill -9 $PIDS
fi