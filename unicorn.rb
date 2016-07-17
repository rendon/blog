# Set the working application directory
# working_directory "/path/to/your/app"
working_directory "/home/rendon/blog"

# Unicorn PID file location
# pid "/path/to/pids/unicorn.pid"
pid "/home/rendon/blog/pids/unicorn.pid"

# Path to logs
# stderr_path "/path/to/logs/unicorn.log"
# stdout_path "/path/to/logs/unicorn.log"
stderr_path "/home/rendon/blog/logs/unicorn.log"
stdout_path "/home/rendon/blog/logs/unicorn.log"

# Unicorn socket
# listen "/tmp/unicorn.[app name].sock"
listen "/tmp/unicorn.blog.sock"

# Number of processes
# worker_processes 4
worker_processes 4

# Time-out
timeout 30
