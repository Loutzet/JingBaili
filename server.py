# server.py
import socket

def start_server(host='127.0.0.1', port=65432):
    # 创建一个 TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # 绑定 socket 到地址和端口
        s.bind((host, port))
        # 开始监听，参数指定可以挂起的最大连接数
        s.listen()
        print(f"服务器启动，监听 {host}:{port}")
        
        while True:
            # 等待客户端连接
            conn, addr = s.accept()
            with conn:
                print(f"连接来自 {addr}")
                while True:
                    # 接收客户端发送的数据，缓冲区大小为1024字节
                    data = conn.recv(1024000)
                    if not data:
                        break
                    print(f"收到来自 {addr} 的数据: {data.decode()}")
                    # 将接收到的数据回传给客户端
                    conn.sendall(data)
                print(f"与 {addr} 的连接已关闭")

if __name__ == "__main__":
    start_server()
