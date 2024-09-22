# client.py
import socket

def start_client(host='127.0.0.1', port=65432):
    # 创建一个 TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # 连接到服务器
        s.connect((host, port))
        print(f"连接到服务器 {host}:{port}")
        
        while True:
            # 获取用户输入
            message = input("请输入要发送的消息（输入 'exit' 退出）：")
            if message.lower() == 'exit':
                print("关闭连接")
                break
            # 发送消息
            s.sendall(message.encode())
            # 接收服务器回传的数据
            data = s.recv(1024)
            print(f"服务器回显: {data.decode()}")

if __name__ == "__main__":
    start_client()
