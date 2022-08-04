FROM gcc:latest
COPY . /ac
WORKDIR /ac/
RUN g++ -o main team-formation-generator.cpp
CMD ["./main"]