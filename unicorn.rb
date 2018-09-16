# Set the working application directory
# working_directory "/path/to/your/app"
working_directory "#{ENV['BLOG_PATH']}"

# Unicorn PID file location
# pid "/path/to/pids/unicorn.pid"
pid "#{ENV['BLOG_PATH']}/pids/unicorn.pid"

# Path to logs
# stderr_path "/path/to/logs/unicorn.log"
# stdout_path "/path/to/logs/unicorn.log"
stderr_path "#{ENV['BLOG_PATH']}/logs/unicorn.log"
stdout_path "#{ENV['BLOG_PATH']}/logs/unicorn.log"

# Unicorn socket
# listen "/tmp/unicorn.[app name].sock"
listen "/tmp/unicorn.blog.sock"

# Number of processes
# worker_processes 4
worker_processes 4

# Time-out
timeout 30
