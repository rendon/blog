# frozen_string_literal: true

# Set the working application directory
# working_directory "/path/to/your/app"
working_directory ENV['BLOG_PATH'].to_s

# Unicorn PID file location
# pid "/path/to/pids/unicorn.pid"
pid "#{ENV['BLOG_PATH']}/pids/unicorn.pid"

# Unicorn socket
# listen "/tmp/unicorn.[app name].sock"
listen '/tmp/unicorn.blog.sock'
listen 8080, tcp_nopush: true

# Number of processes
# worker_processes 4
worker_processes 4

# Time-out
timeout 30
